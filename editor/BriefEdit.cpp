/*
 * Descent 3
 * Copyright (C) 2024 Parallax Software
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// BriefEdit.cpp : implementation file
//

#include "mfc_compatibility.h"
#include "editor.h"
#include "BriefEdit.h"
#include "mono.h"
#include "BriefingParse.h"

#include "BriefBitmapEdit.h"
#include "BriefButtonEdit.h"
#include "BriefMovieEdit.h"
#include "BriefScreenEdit.h"
#include "BriefSoundEdit.h"
#include "BriefTextEdit.h"
#include "Telcom.h"
#include "BriefManage.h"
#include "mem.h"
#include "textaux.h"
#include "ddio.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBriefEdit dialog

tLayoutScreen *PBlayouts;
int *PBnum_layouts;
int TCx, TCy;

CBriefEdit::CBriefEdit(CWnd *pParent /*=NULL*/) : CDialog(CBriefEdit::IDD, pParent) {
  //{{AFX_DATA_INIT(CBriefEdit)
  m_fGlitch = 0.0f;
  m_fStatic = 0.0f;
  m_sTitle = _T("");
  //}}AFX_DATA_INIT
  layouts = NULL;
  num_layouts = 0;
  ParseLayoutScreenFile("BriefingLayouts.txt");
  PBlayouts = layouts;
  PBnum_layouts = &num_layouts;
  layout_bmp = -1;
  TCx = TCy = 0;

  int bm_handle = bm_AllocLoadFileBitmap("TelCom.ogf", 0);
  if (bm_handle > BAD_BITMAP_HANDLE) {

    menutga_LoadHotSpotMap(bm_handle, HOTSPOT_DISPLAY, &hotspotmap, &windowmap);

    TCx = windowmap.wm[MONITOR_MAIN].x;
    TCy = windowmap.wm[MONITOR_MAIN].y;

    FreeHotSpotMapInternals(&hotspotmap);
    FreeViewports();
    if (windowmap.wm)
      mem_free(windowmap.wm);
    bm_FreeBitmap(bm_handle);
  }
}

void CBriefEdit::DoDataExchange(CDataExchange *pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CBriefEdit)
  DDX_Text(pDX, IDC_BRIEF_GLITCH, m_fGlitch);
  DDV_MinMaxFloat(pDX, m_fGlitch, 0.f, 1.f);
  DDX_Text(pDX, IDC_BRIEF_STATIC, m_fStatic);
  DDV_MinMaxFloat(pDX, m_fStatic, 0.f, 1.f);
  DDX_Text(pDX, IDC_BRIEF_TITLE, m_sTitle);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBriefEdit, CDialog)
//{{AFX_MSG_MAP(CBriefEdit)
ON_BN_CLICKED(IDC_BRIEF_EFFECT_BITMAP, OnBriefEffectBitmap)
ON_BN_CLICKED(IDC_BRIEF_EFFECT_BUTTON, OnBriefEffectButton)
ON_BN_CLICKED(IDC_BRIEF_EFFECT_DEL, OnBriefEffectDel)
ON_BN_CLICKED(IDC_BRIEF_EFFECT_EDIT, OnBriefEffectEdit)
ON_BN_CLICKED(IDC_BRIEF_EFFECT_MOVIE, OnBriefEffectMovie)
ON_BN_CLICKED(IDC_BRIEF_EFFECT_SOUND, OnBriefEffectSound)
ON_BN_CLICKED(IDC_BRIEF_EFFECT_TEXT, OnBriefEffectText)
ON_BN_CLICKED(IDC_BRIEF_SCREEN_ADD, OnBriefScreenAdd)
ON_BN_CLICKED(IDC_BRIEF_SCREEN_DEL, OnBriefScreenDel)
ON_BN_CLICKED(IDC_BRIEF_SCREEN_EDIT, OnBriefScreenEdit)
ON_WM_DESTROY()
ON_CBN_SELCHANGE(IDC_BRIEF_SCREEN_LIST, OnSelchangeBriefScreenList)
ON_BN_CLICKED(IDC_BRIEF_SAVE, OnBriefSave)
ON_BN_CLICKED(IDC_LOAD, OnLoad)
ON_WM_TIMER()
ON_BN_CLICKED(IDC_MANAGE, OnManage)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*
 ****************************************************************************
 *			Functions to manipulate effects/screens in briefing editor		*
 ****************************************************************************
 *
 */
bool Briefing_free_called = true; // if this is true it's ok to Init screens
int Briefing_root_screen;
tBriefScreen Briefing_screens[MAX_TELCOM_SCREENS];

//	BriefEditInitScreens
//
//	Initializes the briefing screens so they are empty
void BriefEditInitScreens(void) {
  ASSERT(Briefing_free_called);
  Briefing_free_called = false;

  Briefing_root_screen = -1;

  for (int scr = 0; scr < MAX_TELCOM_SCREENS; scr++) {
    tBriefScreen *bscr = &Briefing_screens[scr];

    bscr->used = false;
    bscr->root_effect = -1;
    bscr->next = -1;
    bscr->prev = -1;
    bscr->layout[0] = '\0';
    bscr->mission_mask_set = 0;
    bscr->mission_mask_unset = 0;

    for (int eff = 0; eff < MAX_EFFECTS_PER_SCREEN; eff++) {
      BriefEditInitEffect(&bscr->effects[eff]);
    }
  }
}

//	BriefEditInitEffect
//
//	Initializes an effect to empty
void BriefEditInitEffect(tBriefEffect *efx) {
  ASSERT(efx);

  memset(efx, 0, sizeof(tBriefEffect));

  efx->type = BE_NONE;
  efx->used = false;
  efx->id = 0;
  efx->text = NULL;
  efx->next = -1;
  efx->prev = -1;
  efx->w = efx->h = -1;
  efx->description[0] = '\0';
}

//	BriefEditFreeScreen
//
//	Frees a screen
void BriefEditFreeScreen(tBriefScreen *bscr) {
  bscr->used = false;
  bscr->root_effect = -1;
  bscr->prev = bscr->next = -1;
  bscr->layout[0] = '\0';

  for (int eff = 0; eff < MAX_EFFECTS_PER_SCREEN; eff++) {
    if (bscr->effects[eff].used) {
      BriefEditFreeEffect(&bscr->effects[eff]);
    }
  }
}

//	BriefEditFreeScreens
//
//	Closes down all the briefing screens, freeing memory
void BriefEditFreeScreens(void) {
  ASSERT(!Briefing_free_called);
  Briefing_free_called = true;

  for (int scr = 0; scr < MAX_TELCOM_SCREENS; scr++) {
    if (Briefing_screens[scr].used) {
      tBriefScreen *bscr = &Briefing_screens[scr];
      BriefEditFreeScreen(bscr);
    }
  }
}

//	BriefEditFreeEffect
//
//	Frees up any memory allocated in an effect
void BriefEditFreeEffect(tBriefEffect *efx) {
  switch (efx->type) {
  case BE_TEXT:
  case BE_BMP:
  case BE_MOVIE:
  case BE_BKG:
  case BE_POLY:
  case BE_SND:
  case BE_BUTTON:
    break;
  default:
    Int3(); // Get Jeff
  };

  if (efx->text) {
    mem_free(efx->text);
    efx->text = NULL;
  }

  efx->used = false;
  efx->next = efx->prev = -1;
  efx->description[0] = '\0';
  efx->id = 0;
  efx->type = BE_NONE;
}

void BuildMissionFlagMask(uint32_t mask, char *string, uint8_t isset) {
  int counter = 0;
  int index = 0;
  uint32_t bit = 0x01;
  char temp[10];

  for (index = 0; index < 32; index++) {
    if (mask & bit) {
      if (isset)
        strcat(string, "isset ");
      else
        strcat(string, "isnset ");
      sprintf(temp, "%d ", counter);
      strcat(string, temp);
    }
    counter++;
    bit = bit << 1;
  }
}

//	BriefEditSaveScreens
//
//	Saves out the screens to a briefing file
uint8_t BriefEditSaveScreens(char *filename, CComboBox *screen_combo, BriefGlobalValues *glob) {
  CFILE *file = cfopen(filename, "wt");
  if (!file)
    return 0;

  int curr_screen = Briefing_root_screen;
  int curr_effect;
  char buffer[9 * 1024];
  char tempbuffer[512];
  int screen_count = 0;

  // Write out global information
  sprintf(buffer, "$title \"%s\"", glob->title);
  cf_WriteString(file, buffer);
  sprintf(buffer, "$glitch %.3f", glob->glitch_val);
  cf_WriteString(file, buffer);
  sprintf(buffer, "$static %.3f", glob->static_val);
  cf_WriteString(file, buffer);

  cf_WriteString(file, "\n");

  while (curr_screen != -1) {
    ASSERT(curr_screen >= 0 && curr_screen < MAX_TELCOM_SCREENS);
    ASSERT(Briefing_screens[curr_screen].used);

    curr_effect = Briefing_screens[curr_screen].root_effect;
    tBriefEffect *effects = Briefing_screens[curr_screen].effects;

    char masksetstr[256], maskunsetstr[256];
    masksetstr[0] = '\0';
    maskunsetstr[0] = '\0';
    if (Briefing_screens[curr_screen].mission_mask_set) {
      BuildMissionFlagMask(Briefing_screens[curr_screen].mission_mask_set, masksetstr, 1);
    }
    if (Briefing_screens[curr_screen].mission_mask_unset) {
      BuildMissionFlagMask(Briefing_screens[curr_screen].mission_mask_unset, maskunsetstr, 0);
    }

    // Write out start screen
    screen_combo->GetLBText(screen_count, tempbuffer);
    if (Briefing_screens[curr_screen].layout[0] != '\0')
      sprintf(buffer, "$screen %d %s %s desc \"%s\" layout \"%s\" start", screen_count, masksetstr, maskunsetstr,
              tempbuffer, Briefing_screens[curr_screen].layout);
    else
      sprintf(buffer, "$screen %d %s %s desc \"%s\" start", screen_count, masksetstr, maskunsetstr, tempbuffer);
    cf_WriteString(file, buffer);

    while (curr_effect != -1) {
      ASSERT(curr_effect >= 0 && curr_effect < MAX_EFFECTS_PER_SCREEN);
      ASSERT(effects[curr_effect].used);

      // Write out effect data
      switch (effects[curr_effect].type) {
      case BE_TEXT: {
        TCTEXTDESC *desc = &effects[curr_effect].text_desc;

        switch (desc->type) {
        case TC_TEXT_STATIC:
          strcpy(tempbuffer, "None");
          break;
        case TC_TEXT_SCROLL:
          switch (desc->flags) {
          case TC_TEXTF_L2R:
            strcpy(tempbuffer, "scroll_l2r");
            break;
          case TC_TEXTF_R2L:
            strcpy(tempbuffer, "scroll_r2l");
            break;
          case TC_TEXTF_T2B:
            strcpy(tempbuffer, "scroll_t2b");
            break;
          case TC_TEXTF_B2T:
            strcpy(tempbuffer, "scroll_b2t");
            break;
          default:
            strcpy(tempbuffer, "None");
            break;
          }
          break;
        case TC_TEXT_FADE:
          switch (desc->flags) {
          case TC_TEXTF_IN:
            strcpy(tempbuffer, "fade_in");
            break;
          case TC_TEXTF_OUT:
            strcpy(tempbuffer, "fade_out");
            break;
          default:
            strcpy(tempbuffer, "fade_in");
            break;
          }
          break;
        case TC_TEXT_FLASH:
          strcpy(tempbuffer, "flash");
          break;
        default:
          strcpy(tempbuffer, "None");
        }

        uint8_t red, green, blue;
        red = GR_COLOR_RED(desc->color);
        green = GR_COLOR_GREEN(desc->color);
        blue = GR_COLOR_BLUE(desc->color);

        char font_str[20];
        switch (desc->font) {
        case BBRIEF_FONT_INDEX:
          strcpy(font_str, "lg_brief");
          break;
        default:
          strcpy(font_str, "sm_brief");
          break;
        }

        char masksetstr[256], maskunsetstr[256];
        masksetstr[0] = '\0';
        maskunsetstr[0] = '\0';
        if (desc->mission_mask_set) {
          BuildMissionFlagMask(desc->mission_mask_set, masksetstr, 1);
        }
        if (desc->mission_mask_unset) {
          BuildMissionFlagMask(desc->mission_mask_unset, maskunsetstr, 0);
        }

        sprintf(buffer,
                "$text effect %s font %s %s speed %0.3f box %d,%d,%d,%d color %d,%d,%d desc \"%s\" id %d starttime "
                "%0.3f %s %s show",
                tempbuffer, font_str, (desc->caps & TCTD_TABSTOP) ? "tabstop" : "", desc->speed, desc->textbox.left,
                desc->textbox.right, desc->textbox.top, desc->textbox.bottom, red, green, blue,
                effects[curr_effect].description, effects[curr_effect].id, desc->waittime, masksetstr, maskunsetstr);
        cf_WriteString(file, buffer);

        // now write out all the text
        const char *p = effects[curr_effect].text;
        while (p) {
          p = textaux_CopyTextLine(p, buffer);
          cf_WriteString(file, buffer);
        }

        cf_WriteString(file, "$endtext");
      } break;
      case BE_BMP: {
        TCBMPDESC *desc = &effects[curr_effect].bmp_desc;
        switch (desc->type) {
        case TC_BMP_STATIC:
          strcpy(tempbuffer, "None");
          break;
        case TC_BMP_BLUR:
          if (desc->flags == TC_BMPF_IN)
            strcpy(tempbuffer, "Blur_in");
          else
            strcpy(tempbuffer, "Blur_out");
          break;
        case TC_BMP_SCANLINE:
          if (desc->flags == TC_BMPF_IN)
            strcpy(tempbuffer, "Scan_in");
          else
            strcpy(tempbuffer, "Scan_out");
          break;
        case TC_BMP_INVERT:
          if (desc->flags == TC_BMPF_IN)
            strcpy(tempbuffer, "Invert_in");
          else
            strcpy(tempbuffer, "Invert_out");
          break;
        case TC_BMP_STRETCH:
          if (desc->flags == TC_BMPF_IN)
            strcpy(tempbuffer, "Stretch_in");
          else
            strcpy(tempbuffer, "Stretch_out");
          break;
        default:
          strcpy(tempbuffer, "None");
          break;
        }

        char masksetstr[256], maskunsetstr[256];
        masksetstr[0] = '\0';
        maskunsetstr[0] = '\0';
        if (desc->mission_mask_set) {
          BuildMissionFlagMask(desc->mission_mask_set, masksetstr, 1);
        }
        if (desc->mission_mask_unset) {
          BuildMissionFlagMask(desc->mission_mask_unset, maskunsetstr, 0);
        }

        char no_render[32];
        if (desc->flags & TC_NOEARLYRENDER)
          strcpy(no_render, "no_early_rend");
        else
          *no_render = '\0';

        sprintf(buffer, "$bitmap effect %s starttime %.3f %s speed %.3f position %d,%d %s %s desc \"%s\" show \"%s\"",
                tempbuffer, desc->waittime, no_render, desc->speed, desc->x, desc->y, masksetstr, maskunsetstr,
                effects[curr_effect].description, desc->filename);
        cf_WriteString(file, buffer);
      } break;
      case BE_MOVIE: {
        TCMOVIEDESC *desc = &effects[curr_effect].movie_desc;
        if (desc->looping)
          strcpy(tempbuffer, "looping");
        else
          tempbuffer[0] = '\0';

        char masksetstr[256], maskunsetstr[256];
        masksetstr[0] = '\0';
        maskunsetstr[0] = '\0';
        if (desc->mission_mask_set) {
          BuildMissionFlagMask(desc->mission_mask_set, masksetstr, 1);
        }
        if (desc->mission_mask_unset) {
          BuildMissionFlagMask(desc->mission_mask_unset, maskunsetstr, 0);
        }

        sprintf(buffer, "$movie position %d,%d fps %.3f %s starttime %.3f %s %s desc \"%s\" show \"%s\"", desc->x,
                desc->y, desc->fps, tempbuffer, desc->waittime, masksetstr, maskunsetstr,
                effects[curr_effect].description, desc->filename);
        cf_WriteString(file, buffer);
      } break;
      case BE_BKG: {
        Int3();
      } break;
      case BE_POLY: {
        Int3();
      } break;
      case BE_SND: {
        TCSNDDESC *desc = &effects[curr_effect].snd_desc;
        if (desc->once)
          strcpy(tempbuffer, "once");
        else
          tempbuffer[0] = '\0';

        char masksetstr[256], maskunsetstr[256];
        masksetstr[0] = '\0';
        maskunsetstr[0] = '\0';
        if (desc->mission_mask_set) {
          BuildMissionFlagMask(desc->mission_mask_set, masksetstr, 1);
        }
        if (desc->mission_mask_unset) {
          BuildMissionFlagMask(desc->mission_mask_unset, maskunsetstr, 0);
        }

        sprintf(buffer, "$sound %s starttime %.3f %s %s desc \"%s\" play \"%s\"", tempbuffer, desc->waittime,
                masksetstr, maskunsetstr, effects[curr_effect].description, desc->filename);
        cf_WriteString(file, buffer);
      } break;
      case BE_BUTTON: {
        TCBUTTONDESC *desc = &effects[curr_effect].button_desc;
        char ctype[20];

        switch (desc->click_type) {
        case CLICKTYPE_CLICKDOWN:
          strcpy(ctype, "ClickDown");
          break;
        case CLICKTYPE_CLICKUP:
          strcpy(ctype, "ClickUp");
          break;
        case CLICKTYPE_DOWN:
          strcpy(ctype, "HoldDown");
          break;
        default:
          strcpy(ctype, "ClickUp");
          break;
        }
        switch (desc->button_type) {
        case BUTT_UPARROW:
          strcpy(tempbuffer, "Up");
          break;
        case BUTT_DOWNARROW:
          strcpy(tempbuffer, "Down");
          break;
        case BUTT_NEXTPAGE:
          strcpy(tempbuffer, "Next");
          break;
        case BUTT_PREVPAGE:
          strcpy(tempbuffer, "Prev");
          break;
        case BUTT_QUIT:
          strcpy(tempbuffer, "Quit");
          break;
        case BUTT_JUMP:
          sprintf(tempbuffer, "Jump %d", desc->jump_page);
          break;
        default:
          strcpy(tempbuffer, "Next");
          break;
        }

        char flash_info[_MAX_PATH + 256];
        flash_info[0] = '\0';
        if (desc->osflags & OBF_FLASH)
          sprintf(flash_info, "flash %.3f \"%s\" \"%s\"", desc->flash_time, desc->flash_filename,
                  desc->flash_filename_focus);

        char glow_fname[_MAX_PATH + 4];
        glow_fname[0] = '\0';
        if (desc->osflags == OBF_GLOW)
          sprintf(glow_fname, "\"%s\" \"%s\"", desc->flash_filename, desc->flash_filename_focus);

        char glow_id[7];
        glow_id[0] = '\0';
        if (desc->osflags & OBF_GLOW)
          strcpy(glow_id, "glow");

        char masksetstr[256], maskunsetstr[256];
        masksetstr[0] = '\0';
        maskunsetstr[0] = '\0';
        if (desc->mission_mask_set) {
          BuildMissionFlagMask(desc->mission_mask_set, masksetstr, 1);
        }
        if (desc->mission_mask_unset) {
          BuildMissionFlagMask(desc->mission_mask_unset, maskunsetstr, 0);
        }

        sprintf(buffer,
                "$button %d,%d type %s %s %s click %s id %d desc \"%s\" parent_id %d sibling_id %d %s %s show \"%s\" "
                "\"%s\" %s",
                desc->x, desc->y, tempbuffer, flash_info, glow_id, ctype, effects[curr_effect].id,
                effects[curr_effect].description, desc->parent_id, desc->sibling_id, masksetstr, maskunsetstr,
                desc->filename, desc->filename_focus, glow_fname);
        cf_WriteString(file, buffer);
      } break;
      default:
        Int3();
        break;
      }

      curr_effect = effects[curr_effect].next;
    }

    // Write out End screen
    cf_WriteString(file, "$endscreen\n");

    curr_screen = Briefing_screens[curr_screen].next;
    screen_count++;
  }

  cfclose(file);
  return 1;
}

struct {
  int current_screen;
  char title[128];
  CComboBox *scombo, *ecombo;
  BriefGlobalValues *glob;
} BEParseInfo;

void BEGetCurScreenEffect(int *ret_screen, int *ret_effect) {
  if (ret_screen)
    *ret_screen = -1;
  if (ret_effect)
    *ret_effect = -1;

  // Get the current screen
  int curr_screen = BEParseInfo.scombo->GetCurSel();
  if (curr_screen == CB_ERR) {
    return;
  }

  // now we need to get the real effect num
  int node = Briefing_root_screen;
  int count = curr_screen;

  while (node != -1 && count > 0) {
    count--;
    node = Briefing_screens[node].next;
  }

  ASSERT(count == 0); // we better be at 0 here
  ASSERT(node >= 0 && node < MAX_TELCOM_SCREENS);
  ASSERT(Briefing_screens[node].used);

  if (count != 0)
    return;

  if (ret_screen)
    *ret_screen = node;

  if (!ret_effect)
    return;

  // Get the current screen
  int curr_effect = BEParseInfo.ecombo->GetCurSel();
  if (curr_effect == CB_ERR) {
    return;
  }

  // now we need to get the real effect num
  node = Briefing_screens[curr_screen].root_effect;
  count = curr_effect;

  while (node != -1 && count > 0) {
    count--;
    node = Briefing_screens[curr_screen].effects[node].next;
  }

  ASSERT(count == 0); // we better be at 0 here
  if (count != 0)
    return;

  if (ret_effect)
    *ret_effect = node;
}

bool BEAllocEffect(int *ret_screen, int *ret_effect) {
  // Get the current screen
  int curr_screen;
  BEGetCurScreenEffect(&curr_screen, NULL);
  if (curr_screen == -1) {
    return false;
  }

  ASSERT(curr_screen >= 0 && curr_screen < MAX_TELCOM_SCREENS);
  ASSERT(Briefing_screens[curr_screen].used);

  // Trace though the effect list and add the effect
  int curr_effect = -1;
  int node = Briefing_screens[curr_screen].root_effect;
  tBriefScreen *bscr = &Briefing_screens[curr_screen];
  int i;
  for (i = 0; i < MAX_EFFECTS_PER_SCREEN; i++) {
    if (!bscr->effects[i].used) {
      curr_effect = i;
      break;
    }
  }
  if (curr_effect == -1) {
    // no available effects
    return false;
  }

  bscr->effects[i].used = true;
  if (node == -1) {
    // first effect for screen
    bscr->root_effect = curr_effect;
    bscr->effects[curr_effect].prev = bscr->effects[curr_effect].next = -1;
    *ret_screen = curr_screen;
    *ret_effect = curr_effect;
    return true;
  } else {
    // get to the end of effects for list
    while (bscr->effects[node].next != -1) {
      node = bscr->effects[node].next;
    }

    // when we get here node should at the end of the list
    bscr->effects[node].next = curr_effect;
    bscr->effects[curr_effect].next = -1;
    bscr->effects[curr_effect].prev = node;
    *ret_screen = curr_screen;
    *ret_effect = curr_effect;
    return true;
  }

  Int3();
  return false; // unknown error
}

void BEAddTextEffect(TCTEXTDESC *desc, char *text, char *description, int id) {
  int curr_screen, curr_effect;
  if (!BEAllocEffect(&curr_screen, &curr_effect))
    return;

  tBriefScreen *bscr = &Briefing_screens[curr_screen];
  tBriefEffect *befx = &bscr->effects[curr_effect];
  TCTEXTDESC *dest = &befx->text_desc;

  if (strlen(description) == 0)
    strcpy(description, "Text");
  befx->type = BE_TEXT;
  strcpy(befx->description, description);
  befx->id = id;

  dest->caps = desc->caps;
  memcpy(&dest->textbox, &desc->textbox, sizeof(tc_text));
  dest->font = desc->font;
  dest->color = desc->color;
  dest->flags = desc->flags;
  dest->speed = desc->speed;
  dest->looping = desc->looping;
  dest->waittime = desc->waittime;
  dest->type = desc->type;
  dest->mission_mask_set = desc->mission_mask_set;
  dest->mission_mask_unset = desc->mission_mask_unset;

  if (befx->text) {
    mem_free(befx->text);
    befx->text = NULL;
  }
  befx->text = (char *)mem_malloc(strlen(text) + 1);
  ASSERT(befx->text);
  strcpy(befx->text, text);

  // Setup for items not set with caps
  if (!(dest->caps & TCTD_FONT)) {
    dest->caps |= TCTD_FONT;
    dest->font = BRIEF_FONT_INDEX;
  }
  if (!(dest->caps & TCTD_COLOR)) {
    dest->caps |= TCTD_COLOR;
    dest->color = GR_GREEN;
  }
  if (!(dest->caps & TCTD_SPEED)) {
    dest->caps |= TCTD_SPEED;
    dest->speed = 1;
  }
  if (!(dest->caps & TCTD_LOOPING)) {
    dest->caps |= TCTD_LOOPING;
    dest->looping = false;
  }
  if (!(dest->caps & TCTD_WAITTIME)) {
    dest->caps |= TCTD_WAITTIME;
    dest->waittime = 0;
  }
  if (!(dest->caps & TCTD_TEXTBOX)) {
    dest->caps |= TCTD_TEXTBOX;
    dest->textbox.left = dest->textbox.top = 0;
    dest->textbox.right = 639;
    dest->textbox.bottom = 479;
  }
}

void BEAddBmpEffect(TCBMPDESC *desc, char *description) {
  int curr_screen, curr_effect;
  if (!BEAllocEffect(&curr_screen, &curr_effect))
    return;

  tBriefScreen *bscr = &Briefing_screens[curr_screen];
  tBriefEffect *befx = &bscr->effects[curr_effect];
  TCBMPDESC *dest = &befx->bmp_desc;

  if (strlen(description) == 0)
    strcpy(description, "Bitmap");
  befx->type = BE_BMP;
  strcpy(befx->description, description);

  dest->type = desc->type;
  dest->flags = desc->flags;
  dest->caps = desc->caps;
  dest->x = desc->x;
  dest->y = desc->y;
  dest->looping = desc->looping;
  dest->waittime = desc->waittime;
  dest->speed = desc->speed;
  dest->mission_mask_set = desc->mission_mask_set;
  dest->mission_mask_unset = desc->mission_mask_unset;
  strcpy(dest->filename, desc->filename);

  // Setup values not set with caps
  if (!(dest->caps & TCBD_XY)) {
    dest->caps |= TCBD_XY;
    dest->x = dest->y = 0;
  }
  if (!(dest->caps & TCBD_LOOPING)) {
    dest->caps |= TCBD_LOOPING;
    dest->looping = false;
  }
  if (!(dest->caps & TCBD_WAITTIME)) {
    dest->caps |= TCBD_WAITTIME;
    dest->waittime = 0;
  }
  if (!(dest->caps & TCBD_SPEED)) {
    dest->caps |= TCBD_SPEED;
    dest->speed = 2;
  }
}

void BEAddMovieEffect(TCMOVIEDESC *desc, char *description) {
  int curr_screen, curr_effect;
  if (!BEAllocEffect(&curr_screen, &curr_effect))
    return;

  tBriefScreen *bscr = &Briefing_screens[curr_screen];
  tBriefEffect *befx = &bscr->effects[curr_effect];
  TCMOVIEDESC *dest = &befx->movie_desc;

  if (strlen(description) == 0)
    strcpy(description, "Movie");
  befx->type = BE_MOVIE;
  strcpy(befx->description, description);

  dest->caps = desc->caps;
  dest->type = desc->type;
  dest->x = desc->x;
  dest->y = desc->y;
  dest->mission_mask_set = desc->mission_mask_set;
  dest->mission_mask_unset = desc->mission_mask_unset;
  strcpy(dest->filename, desc->filename);
  dest->looping = desc->looping;
  dest->fps = desc->fps;
  dest->waittime = desc->waittime;

  // Setup values without caps
  if (!(dest->caps & TCMD_XY)) {
    dest->caps |= TCMD_XY;
    dest->x = dest->y = 0;
  }
  if (!(dest->caps & TCMD_LOOPING)) {
    dest->caps |= TCMD_LOOPING;
    dest->looping = false;
  }
  if (!(dest->caps & TCMD_WAITTIME)) {
    dest->caps |= TCMD_WAITTIME;
    dest->waittime = 0;
  }
  if (!(dest->caps & TCMD_FPS)) {
    dest->caps |= TCMD_FPS;
    dest->fps = 20;
  }
}

void BEAddBkgEffect(TCBKGDESC *desc, char *description) {
  int curr_screen, curr_effect;
  if (!BEAllocEffect(&curr_screen, &curr_effect))
    return;

  tBriefScreen *bscr = &Briefing_screens[curr_screen];
  tBriefEffect *befx = &bscr->effects[curr_effect];
  TCBKGDESC *dest = &befx->bkg_desc;

  if (strlen(description) == 0)
    strcpy(description, "Background");
  befx->type = BE_BKG;
  strcpy(befx->description, description);

  dest->caps = desc->caps;
  dest->type = desc->type;
  dest->id = desc->id;
  dest->color = desc->color;
  dest->waittime = desc->waittime;
  dest->mission_mask_set = desc->mission_mask_set;
  dest->mission_mask_unset = desc->mission_mask_unset;

  // setup values without caps
  if (!(dest->caps & TCBGD_ID)) {
    dest->caps |= TCBGD_ID;
    dest->id = 0;
  }
  if (!(dest->caps & TCBGD_WAITTIME)) {
    dest->caps |= TCBGD_WAITTIME;
    dest->waittime = 0;
  }
  if (!(dest->caps & TCBGD_COLOR)) {
    dest->caps |= TCBGD_COLOR;
    dest->color = GR_BLUE;
  }
}

void BEAddPolyEffect(TCPOLYDESC *desc, char *description) {
  int curr_screen, curr_effect;
  if (!BEAllocEffect(&curr_screen, &curr_effect))
    return;

  tBriefScreen *bscr = &Briefing_screens[curr_screen];
  tBriefEffect *befx = &bscr->effects[curr_effect];
  TCPOLYDESC *dest = &befx->poly_desc;

  if (strlen(description) == 0)
    strcpy(description, "PolyModel");
  befx->type = BE_POLY;
  strcpy(befx->description, description);

  dest->caps = desc->caps;
  dest->type = desc->type;
  dest->pos_x = desc->pos_x;
  dest->pos_y = desc->pos_y;
  dest->pos_z = desc->pos_z;
  dest->rot_x = desc->rot_x;
  dest->rot_y = desc->rot_y;
  dest->rot_z = desc->rot_z;
  dest->ori_x = desc->ori_x;
  dest->ori_y = desc->ori_y;
  dest->ori_z = desc->ori_z;
  dest->flags = desc->flags;
  dest->waittime = desc->waittime;
  dest->mission_mask_set = desc->mission_mask_set;
  dest->mission_mask_unset = desc->mission_mask_unset;
  strcpy(dest->polyname, desc->polyname);

  Int3(); // Why are we here!?!?!?? This effect isn't even in yet
  if (!(dest->caps & TCPM_SPEED)) {
    dest->caps |= TCPM_SPEED;
    dest->waittime = 0;
  }
}

void BEAddSoundEffect(TCSNDDESC *desc, char *description) {
  int curr_screen, curr_effect;
  if (!BEAllocEffect(&curr_screen, &curr_effect))
    return;

  tBriefScreen *bscr = &Briefing_screens[curr_screen];
  tBriefEffect *befx = &bscr->effects[curr_effect];
  TCSNDDESC *dest = &befx->snd_desc;

  if (strlen(description) == 0)
    strcpy(description, "Sound");
  befx->type = BE_SND;
  strcpy(befx->description, description);

  dest->caps = desc->caps;
  dest->type = desc->type;
  dest->once = desc->once;
  dest->waittime = desc->waittime;
  dest->mission_mask_set = desc->mission_mask_set;
  dest->mission_mask_unset = desc->mission_mask_unset;
  strcpy(dest->filename, desc->filename);

  // Setup values without caps
  if (!(dest->caps & TCSD_WAITTIME)) {
    dest->caps |= TCSD_WAITTIME;
    dest->waittime = 0;
  }
  if (!(dest->caps & TCSD_ONCE)) {
    dest->caps |= TCSD_ONCE;
    dest->once = true;
  }
}

void BEAddButtonEffect(TCBUTTONDESC *desc, char *description, int id) {
  int curr_screen, curr_effect;
  if (!BEAllocEffect(&curr_screen, &curr_effect))
    return;

  tBriefScreen *bscr = &Briefing_screens[curr_screen];
  tBriefEffect *befx = &bscr->effects[curr_effect];
  TCBUTTONDESC *dest = &befx->button_desc;

  if (strlen(description) == 0)
    strcpy(description, "Button");
  befx->type = BE_BUTTON;
  strcpy(befx->description, description);
  befx->id = id;

  strcpy(dest->filename, desc->filename);
  strcpy(dest->filename_focus, desc->filename_focus);
  if (desc->flasher) {
    strcpy(dest->flash_filename, desc->flash_filename);
    strcpy(dest->flash_filename_focus, desc->flash_filename_focus);
  } else {
    dest->flash_filename[0] = '\0';
    dest->flash_filename_focus[0] = '\0';
  }
  dest->sibling_id = desc->sibling_id;
  dest->parent_id = desc->parent_id;
  dest->x = desc->x;
  dest->y = desc->y;
  dest->w = desc->w;
  dest->h = desc->h;
  dest->osflags = desc->osflags;
  dest->flash_time = desc->flash_time;
  dest->button_type = desc->button_type;
  dest->click_type = desc->click_type;
  dest->flasher = desc->flasher;
  dest->mission_mask_set = desc->mission_mask_set;
  dest->mission_mask_unset = desc->mission_mask_unset;
  dest->jump_page = desc->jump_page;
}

void BEStartScreen(int screen_num, char *description, char *layout, uint32_t mask_set, uint32_t mask_unset) {
  int scr_to_add = -1;
  for (int i = 0; i < MAX_TELCOM_SCREENS; i++) {
    if (!Briefing_screens[i].used) {
      scr_to_add = i;
      break;
    }
  }
  if (scr_to_add == -1) {
    Int3(); // out of screens
    return;
  }

  if (strlen(description) == 0) {
    sprintf(description, "Screen %d", screen_num);
  }

  BEParseInfo.current_screen++;
  Briefing_screens[scr_to_add].used = true;
  Briefing_screens[scr_to_add].mission_mask_set = mask_set;
  Briefing_screens[scr_to_add].mission_mask_unset = mask_unset;

  if (layout)
    strcpy(Briefing_screens[scr_to_add].layout, layout);
  else
    Briefing_screens[scr_to_add].layout[0] = '\0';

  if (Briefing_root_screen == -1) {
    Briefing_root_screen = scr_to_add;
    Briefing_screens[scr_to_add].prev = Briefing_screens[scr_to_add].next = -1;
  } else {
    int node = Briefing_root_screen;
    while (Briefing_screens[node].next != -1) {
      node = Briefing_screens[node].next;
    }
    Briefing_screens[node].next = scr_to_add;
    Briefing_screens[scr_to_add].prev = node;
    Briefing_screens[scr_to_add].next = -1;
  }
  int sel = BEParseInfo.scombo->AddString(description);
  ASSERT(sel >= 0);
  BEParseInfo.scombo->SetCurSel(sel);
}

void BEEndScreen() {}

void BESetTitle(char *title) { strcpy(BEParseInfo.glob->title, title); }

void BESetStatic(float amount) { BEParseInfo.glob->static_val = amount; }

void BESetGlitch(float amount) { BEParseInfo.glob->glitch_val = amount; }

void BEAddVoice(char *filename, int flags, char *description) {}

//  BriefEditLoadScreens
//
//	Loads in screens from a briefing file
uint8_t BriefEditLoadScreens(char *filename, CComboBox *screen_combo, CComboBox *effect_combo,
                             BriefGlobalValues *glob) {
  BEParseInfo.current_screen = 0;
  BEParseInfo.title[0] = '\0';
  BEParseInfo.scombo = screen_combo;
  BEParseInfo.ecombo = effect_combo;
  BEParseInfo.glob = glob;

  glob->title[0] = '\0';
  glob->static_val = glob->glitch_val = 0;

  CBriefParse engine;
  tBriefParseCallbacks pb_callbacks;

  pb_callbacks.AddTextEffect = BEAddTextEffect;
  pb_callbacks.AddBmpEffect = BEAddBmpEffect;
  pb_callbacks.AddMovieEffect = BEAddMovieEffect;
  pb_callbacks.AddBkgEffect = BEAddBkgEffect;
  pb_callbacks.AddPolyEffect = BEAddPolyEffect;
  pb_callbacks.AddSoundEffect = BEAddSoundEffect;
  pb_callbacks.AddButtonEffect = BEAddButtonEffect;
  pb_callbacks.StartScreen = BEStartScreen;
  pb_callbacks.EndScreen = BEEndScreen;
  pb_callbacks.LoopCallback = NULL;
  pb_callbacks.SetTitle = BESetTitle;
  pb_callbacks.SetStatic = BESetStatic;
  pb_callbacks.SetGlitch = BESetGlitch;
  pb_callbacks.AddVoice = BEAddVoice;

  engine.SetCallbacks(&pb_callbacks);
  return engine.ParseBriefing(filename);
}

//	BriefEditAllocateEffect
//
//	Allocates an effect (links it and all) to be edited.  Returns false on error
bool CBriefEdit::BriefEditAllocateEffect(int *ret_screen, int *ret_effect) {
  UpdateData(true);

  // Get the current screen
  int curr_screen;
  BriefEditGetCurScreenEffect(&curr_screen, NULL);
  if (curr_screen == -1) {
    MessageBox("You Need To Create A Screen", "Error");
    return false;
  }

  ASSERT(curr_screen >= 0 && curr_screen < MAX_TELCOM_SCREENS);
  ASSERT(Briefing_screens[curr_screen].used);

  // Trace though the effect list and add the effect
  int curr_effect = -1;
  int node = Briefing_screens[curr_screen].root_effect;
  tBriefScreen *bscr = &Briefing_screens[curr_screen];
  int i;
  for (i = 0; i < MAX_EFFECTS_PER_SCREEN; i++) {
    if (!bscr->effects[i].used) {
      curr_effect = i;
      break;
    }
  }
  if (curr_effect == -1) {
    // no available effects
    MessageBox("No More Effects Available For This Screen", "Error");
    return false;
  }

  bscr->effects[i].used = true;
  if (node == -1) {
    // first effect for screen
    bscr->root_effect = curr_effect;
    bscr->effects[curr_effect].prev = bscr->effects[curr_effect].next = -1;
    *ret_screen = curr_screen;
    *ret_effect = curr_effect;
    return true;
  } else {
    // get to the end of effects for list
    while (bscr->effects[node].next != -1) {
      node = bscr->effects[node].next;
    }

    // when we get here node should at the end of the list
    bscr->effects[node].next = curr_effect;
    bscr->effects[curr_effect].next = -1;
    bscr->effects[curr_effect].prev = node;
    *ret_screen = curr_screen;
    *ret_effect = curr_effect;
    return true;
  }

  Int3();
  return false; // unknown error
}

//	BriefEditGetCurScreenEffect
//
//	Fills in the current screen and effect that is being worked on
void CBriefEdit::BriefEditGetCurScreenEffect(int *ret_screen, int *ret_effect) {
  if (ret_screen)
    *ret_screen = -1;
  if (ret_effect)
    *ret_effect = -1;

  UpdateData(true);

  // Get the current screen
  CComboBox *combo = (CComboBox *)GetDlgItem(IDC_BRIEF_SCREEN_LIST);
  int curr_screen = combo->GetCurSel();
  if (curr_screen == CB_ERR) {
    return;
  }

  // now we need to get the real effect num
  int node = Briefing_root_screen;
  int count = curr_screen;

  while (node != -1 && count > 0) {
    count--;
    node = Briefing_screens[node].next;
  }

  ASSERT(count == 0); // we better be at 0 here
  ASSERT(node >= 0 && node < MAX_TELCOM_SCREENS);
  ASSERT(Briefing_screens[node].used);

  if (count != 0)
    return;

  if (ret_screen)
    *ret_screen = node;

  if (!ret_effect)
    return;

  // Get the current screen
  combo = (CComboBox *)GetDlgItem(IDC_BRIEF_EFFECT_LIST);
  int curr_effect = combo->GetCurSel();
  if (curr_effect == CB_ERR) {
    return;
  }

  // now we need to get the real effect num
  node = Briefing_screens[curr_screen].root_effect;
  count = curr_effect;

  while (node != -1 && count > 0) {
    count--;
    node = Briefing_screens[curr_screen].effects[node].next;
  }

  //	ASSERT(count==0);	//we better be at 0 here
  if (count != 0)
    return;

  if (ret_effect)
    *ret_effect = node;
}

/////////////////////////////////////////////////////////////////////////////
// CBriefEdit message handlers

void CBriefEdit::OnOK() {
  if (has_changed) {
    // they've made changes but haven't saved
    if (MessageBox("You haven't saved your changes, are you sure you want to quit?", "Confirm", MB_YESNO) != IDYES) {
      return;
    }
  }

  has_changed = false;

  if (layouts)
    mem_free(layouts);
  if (layout_bmp > BAD_BITMAP_HANDLE)
    bm_FreeBitmap(layout_bmp);
  CDialog::OnOK();
}

void CBriefEdit::OnBriefEffectBitmap() {
  int curr;
  BriefEditGetCurScreenEffect(&curr, NULL);

  CBriefBitmapEdit dlg(curr);
  if (dlg.DoModal() == IDOK) {
    has_changed = true;
    int c_scr, c_eff;
    if (!BriefEditAllocateEffect(&c_scr, &c_eff))
      return;

    CComboBox *combo = (CComboBox *)GetDlgItem(IDC_BRIEF_EFFECT_LIST);
    int sel = combo->AddString(dlg.m_sDesc);
    ASSERT(sel >= 0); // out of memory!?
    combo->SetCurSel(sel);
    Briefing_screens[c_scr].effects[c_eff].type = BE_BMP;
    strncpy(Briefing_screens[c_scr].effects[c_eff].description, dlg.m_sDesc.GetBuffer(1), 127);
    Briefing_screens[c_scr].effects[c_eff].description[127] = '\0';

    // retrieve info
    TCBMPDESC *dest = &Briefing_screens[c_scr].effects[c_eff].bmp_desc;
    TCBMPDESC *src = &dlg.desc;

    dest->type = src->type;
    dest->flags = src->flags;
    dest->caps = src->caps;
    dest->x = src->x;
    dest->y = src->y;
    dest->looping = src->looping;
    dest->waittime = src->waittime;
    dest->speed = src->speed;
    dest->mission_mask_set = src->mission_mask_set;
    dest->mission_mask_unset = src->mission_mask_unset;
    strcpy(dest->filename, src->filename);
  }
}

void CBriefEdit::OnBriefEffectButton() {
  CBriefButtonEdit dlg;
  if (dlg.DoModal() == IDOK) {
    has_changed = true;
    int c_scr, c_eff;
    if (!BriefEditAllocateEffect(&c_scr, &c_eff))
      return;

    CComboBox *combo = (CComboBox *)GetDlgItem(IDC_BRIEF_EFFECT_LIST);
    int sel = combo->AddString(dlg.m_sDesc);
    ASSERT(sel >= 0); // out of memory!?
    combo->SetCurSel(sel);
    Briefing_screens[c_scr].effects[c_eff].type = BE_BUTTON;
    strncpy(Briefing_screens[c_scr].effects[c_eff].description, dlg.m_sDesc.GetBuffer(1), 127);
    Briefing_screens[c_scr].effects[c_eff].description[127] = '\0';

    // retrieve info
    TCBUTTONDESC *dest = &Briefing_screens[c_scr].effects[c_eff].button_desc;
    TCBUTTONDESC *src = &dlg.desc;

    strcpy(dest->filename, src->filename);
    strcpy(dest->filename_focus, src->filename_focus);
    strcpy(dest->flash_filename, src->flash_filename);
    strcpy(dest->flash_filename_focus, src->flash_filename_focus);
    dest->sibling_id = src->sibling_id;
    dest->parent_id = src->parent_id;
    dest->x = src->x;
    dest->y = src->y;
    dest->w = src->w;
    dest->h = src->h;
    dest->osflags = src->osflags;
    dest->flash_time = src->flash_time;
    dest->button_type = src->button_type;
    dest->click_type = src->click_type;
    dest->flasher = src->flasher;
    dest->mission_mask_set = src->mission_mask_set;
    dest->mission_mask_unset = src->mission_mask_unset;
    dest->jump_page = src->jump_page;

    Briefing_screens[c_scr].effects[c_eff].id = dlg.m_iID;
  }
}

void CBriefEdit::OnBriefEffectDel() {
  UpdateData(true);
  int curr_screen, curr_effect;
  BriefEditGetCurScreenEffect(&curr_screen, &curr_effect);
  if (curr_screen == -1 || curr_effect == -1) {
    MessageBox("No Effects To Delete", "Error");
    return;
  }

  if (MessageBox("Are You Sure You Want To Delete Effect?", "Confirmation", MB_YESNO) != IDYES)
    return;

  ASSERT(curr_screen >= 0 && curr_screen < MAX_TELCOM_SCREENS);
  ASSERT(curr_effect >= 0 && curr_effect < MAX_EFFECTS_PER_SCREEN);

  tBriefScreen *bscr = &Briefing_screens[curr_screen];
  int prev = bscr->effects[curr_effect].prev;
  int next = bscr->effects[curr_effect].next;

  if (prev == -1)
    bscr->root_effect = next;
  else
    bscr->effects[prev].next = next;

  if (next != -1)
    bscr->effects[next].prev = prev;

  BriefEditFreeEffect(&bscr->effects[curr_effect]);
  CComboBox *combo = (CComboBox *)GetDlgItem(IDC_BRIEF_EFFECT_LIST);
  combo->DeleteString(combo->GetCurSel());
  combo->SetCurSel(0);
  has_changed = true;
  UpdateData(false);
}

void CBriefEdit::OnBriefEffectEdit() {
  CComboBox *combo = (CComboBox *)GetDlgItem(IDC_BRIEF_EFFECT_LIST);
  int curr_effect = combo->GetCurSel();

  int efx_index, scr_index;
  BriefEditGetCurScreenEffect(&scr_index, &efx_index);

  if (scr_index == -1 || efx_index == -1) {
    MessageBox("No Effects To Edit", "Error");
    return;
  }

  tBriefEffect *efx = &Briefing_screens[scr_index].effects[efx_index];

  switch (efx->type) {
  case BE_TEXT: {
    CBriefTextEdit dlg(scr_index, &efx->text_desc, efx->text, efx->id);
    combo->GetLBText(curr_effect, dlg.m_sDesc);
    if (dlg.DoModal() == IDOK) {
      has_changed = true;
      // grab the information from the dialog
      combo->DeleteString(curr_effect);
      combo->InsertString(curr_effect, dlg.m_sDesc);
      combo->SetCurSel(curr_effect);
      strncpy(Briefing_screens[scr_index].effects[efx_index].description, dlg.m_sDesc.GetBuffer(1), 127);
      Briefing_screens[scr_index].effects[efx_index].description[127] = '\0';

      // retrieve info
      TCTEXTDESC *dest = &Briefing_screens[scr_index].effects[efx_index].text_desc;
      TCTEXTDESC *src = &dlg.desc;

      dest->caps = src->caps;
      memcpy(&dest->textbox, &src->textbox, sizeof(tc_text));
      dest->font = src->font;
      dest->color = src->color;
      dest->flags = src->flags;
      dest->speed = src->speed;
      dest->looping = src->looping;
      dest->waittime = src->waittime;
      dest->type = src->type;
      dest->mission_mask_set = src->mission_mask_set;
      dest->mission_mask_unset = src->mission_mask_unset;

      Briefing_screens[scr_index].effects[efx_index].id = dlg.m_iID;

      if (Briefing_screens[scr_index].effects[efx_index].text)
        mem_free(Briefing_screens[scr_index].effects[efx_index].text);

      Briefing_screens[scr_index].effects[efx_index].text = (char *)mem_malloc(dlg.m_Text.GetLength() + 1);
      ASSERT(Briefing_screens[scr_index].effects[efx_index].text);

      if (Briefing_screens[scr_index].effects[efx_index].text) {
        strcpy(Briefing_screens[scr_index].effects[efx_index].text, dlg.m_Text.GetBuffer(1));
      }
    }
  } break;
  case BE_BMP: {
    CBriefBitmapEdit dlg(scr_index, &efx->bmp_desc);
    combo->GetLBText(curr_effect, dlg.m_sDesc);
    if (dlg.DoModal() == IDOK) {
      has_changed = true;
      // grab the information from the dialog
      combo->DeleteString(curr_effect);
      combo->InsertString(curr_effect, dlg.m_sDesc);
      combo->SetCurSel(curr_effect);
      strncpy(Briefing_screens[scr_index].effects[efx_index].description, dlg.m_sDesc.GetBuffer(1), 127);
      Briefing_screens[scr_index].effects[efx_index].description[127] = '\0';

      // retrieve info
      TCBMPDESC *dest = &Briefing_screens[scr_index].effects[efx_index].bmp_desc;
      TCBMPDESC *src = &dlg.desc;

      dest->type = src->type;
      dest->flags = src->flags;
      dest->caps = src->caps;
      dest->x = src->x;
      dest->y = src->y;
      dest->looping = src->looping;
      dest->waittime = src->waittime;
      dest->speed = src->speed;
      dest->mission_mask_set = src->mission_mask_set;
      dest->mission_mask_unset = src->mission_mask_unset;

      strcpy(dest->filename, src->filename);
    }
  } break;
  case BE_MOVIE: {
    CBriefMovieEdit dlg(&efx->movie_desc);
    combo->GetLBText(curr_effect, dlg.m_sDesc);
    if (dlg.DoModal() == IDOK) {
      has_changed = true;
      // grab the information from the dialog
      combo->DeleteString(curr_effect);
      combo->InsertString(curr_effect, dlg.m_sDesc);
      combo->SetCurSel(curr_effect);
      strncpy(Briefing_screens[scr_index].effects[efx_index].description, dlg.m_sDesc.GetBuffer(1), 127);
      Briefing_screens[scr_index].effects[efx_index].description[127] = '\0';

      // retrieve info
      TCMOVIEDESC *dest = &Briefing_screens[scr_index].effects[efx_index].movie_desc;
      TCMOVIEDESC *src = &dlg.desc;

      dest->caps = src->caps;
      dest->type = src->type;
      dest->x = src->x;
      dest->y = src->y;
      strcpy(dest->filename, src->filename);
      dest->looping = src->looping;
      dest->fps = src->fps;
      dest->waittime = src->waittime;
      dest->mission_mask_set = src->mission_mask_set;
      dest->mission_mask_unset = src->mission_mask_unset;
    }
  } break;
  case BE_BKG:
    break;
  case BE_POLY:
    break;
  case BE_SND: {
    CBriefSoundEdit dlg(&efx->snd_desc);
    combo->GetLBText(curr_effect, dlg.m_sDesc);
    if (dlg.DoModal() == IDOK) {
      has_changed = true;
      // grab the information from the dialog
      combo->DeleteString(curr_effect);
      combo->InsertString(curr_effect, dlg.m_sDesc);
      combo->SetCurSel(curr_effect);
      strncpy(Briefing_screens[scr_index].effects[efx_index].description, dlg.m_sDesc.GetBuffer(1), 127);
      Briefing_screens[scr_index].effects[efx_index].description[127] = '\0';

      // retrieve info
      TCSNDDESC *dest = &Briefing_screens[scr_index].effects[efx_index].snd_desc;
      TCSNDDESC *src = &dlg.desc;

      dest->caps = src->caps;
      dest->type = src->type;
      dest->once = src->once;
      dest->waittime = src->waittime;
      dest->mission_mask_set = src->mission_mask_set;
      dest->mission_mask_unset = src->mission_mask_unset;
      strcpy(dest->filename, src->filename);
    }
  } break;
  case BE_BUTTON: {
    CBriefButtonEdit dlg(&efx->button_desc, efx->id);
    combo->GetLBText(curr_effect, dlg.m_sDesc);
    if (dlg.DoModal() == IDOK) {
      has_changed = true;
      // grab the information from the dialog
      combo->DeleteString(curr_effect);
      combo->InsertString(curr_effect, dlg.m_sDesc);
      combo->SetCurSel(curr_effect);
      strncpy(Briefing_screens[scr_index].effects[efx_index].description, dlg.m_sDesc.GetBuffer(1), 127);
      Briefing_screens[scr_index].effects[efx_index].description[127] = '\0';

      // retrieve info
      TCBUTTONDESC *dest = &Briefing_screens[scr_index].effects[efx_index].button_desc;
      TCBUTTONDESC *src = &dlg.desc;

      strcpy(dest->filename, src->filename);
      strcpy(dest->filename_focus, src->filename_focus);
      strcpy(dest->flash_filename, src->flash_filename);
      strcpy(dest->flash_filename_focus, src->flash_filename_focus);
      dest->sibling_id = src->sibling_id;
      dest->parent_id = src->parent_id;
      dest->x = src->x;
      dest->y = src->y;
      dest->w = src->w;
      dest->h = src->h;
      dest->osflags = src->osflags;
      dest->flash_time = src->flash_time;
      dest->button_type = src->button_type;
      dest->click_type = src->click_type;
      dest->flasher = src->flasher;
      dest->mission_mask_set = src->mission_mask_set;
      dest->mission_mask_unset = src->mission_mask_unset;
      dest->jump_page = src->jump_page;

      Briefing_screens[scr_index].effects[efx_index].id = dlg.m_iID;
    }
  } break;
  default:
    Int3();
    return;
    break;
  }
}

void CBriefEdit::OnBriefEffectMovie() {
  CBriefMovieEdit dlg;
  if (dlg.DoModal() == IDOK) {
    has_changed = true;
    int c_scr, c_eff;
    if (!BriefEditAllocateEffect(&c_scr, &c_eff))
      return;

    CComboBox *combo = (CComboBox *)GetDlgItem(IDC_BRIEF_EFFECT_LIST);
    int sel = combo->AddString(dlg.m_sDesc);
    ASSERT(sel >= 0); // out of memory!?
    combo->SetCurSel(sel);
    Briefing_screens[c_scr].effects[c_eff].type = BE_MOVIE;
    strncpy(Briefing_screens[c_scr].effects[c_eff].description, dlg.m_sDesc.GetBuffer(1), 127);
    Briefing_screens[c_scr].effects[c_eff].description[127] = '\0';

    // retrieve info
    TCMOVIEDESC *dest = &Briefing_screens[c_scr].effects[c_eff].movie_desc;
    TCMOVIEDESC *src = &dlg.desc;

    dest->caps = src->caps;
    dest->type = src->type;
    dest->x = src->x;
    dest->y = src->y;
    strcpy(dest->filename, src->filename);
    dest->looping = src->looping;
    dest->fps = src->fps;
    dest->waittime = src->waittime;
    dest->mission_mask_set = src->mission_mask_set;
    dest->mission_mask_unset = src->mission_mask_unset;
  }
}

void CBriefEdit::OnBriefEffectSound() {
  CBriefSoundEdit dlg;
  if (dlg.DoModal() == IDOK) {
    has_changed = true;
    int c_scr, c_eff;
    if (!BriefEditAllocateEffect(&c_scr, &c_eff))
      return;

    CComboBox *combo = (CComboBox *)GetDlgItem(IDC_BRIEF_EFFECT_LIST);
    int sel = combo->AddString(dlg.m_sDesc);
    ASSERT(sel >= 0); // out of memory!?
    combo->SetCurSel(sel);
    Briefing_screens[c_scr].effects[c_eff].type = BE_SND;
    strncpy(Briefing_screens[c_scr].effects[c_eff].description, dlg.m_sDesc.GetBuffer(1), 127);
    Briefing_screens[c_scr].effects[c_eff].description[127] = '\0';

    // retrieve info
    TCSNDDESC *dest = &Briefing_screens[c_scr].effects[c_eff].snd_desc;
    TCSNDDESC *src = &dlg.desc;

    dest->caps = src->caps;
    dest->type = src->type;
    dest->once = src->once;
    dest->waittime = src->waittime;
    dest->mission_mask_set = src->mission_mask_set;
    dest->mission_mask_unset = src->mission_mask_unset;

    strcpy(dest->filename, src->filename);
  }
}

void CBriefEdit::OnBriefEffectText() {
  int curr;
  BriefEditGetCurScreenEffect(&curr, NULL);

  CBriefTextEdit dlg(curr);
  if (dlg.DoModal() == IDOK) {
    has_changed = true;
    int c_scr, c_eff;
    if (!BriefEditAllocateEffect(&c_scr, &c_eff))
      return;

    CComboBox *combo = (CComboBox *)GetDlgItem(IDC_BRIEF_EFFECT_LIST);
    int sel = combo->AddString(dlg.m_sDesc);
    ASSERT(sel >= 0); // out of memory!?
    combo->SetCurSel(sel);
    Briefing_screens[c_scr].effects[c_eff].type = BE_TEXT;
    strncpy(Briefing_screens[c_scr].effects[c_eff].description, dlg.m_sDesc.GetBuffer(1), 127);
    Briefing_screens[c_scr].effects[c_eff].description[127] = '\0';

    // retrieve info
    TCTEXTDESC *dest = &Briefing_screens[c_scr].effects[c_eff].text_desc;
    TCTEXTDESC *src = &dlg.desc;

    dest->caps = src->caps;
    memcpy(&dest->textbox, &src->textbox, sizeof(tc_text));
    dest->font = src->font;
    dest->color = src->color;
    dest->flags = src->flags;
    dest->speed = src->speed;
    dest->looping = src->looping;
    dest->waittime = src->waittime;
    dest->type = src->type;
    dest->mission_mask_set = src->mission_mask_set;
    dest->mission_mask_unset = src->mission_mask_unset;

    Briefing_screens[c_scr].effects[c_eff].id = dlg.m_iID;

    if (Briefing_screens[c_scr].effects[c_eff].text)
      mem_free(Briefing_screens[c_scr].effects[c_eff].text);

    Briefing_screens[c_scr].effects[c_eff].text = (char *)mem_malloc(dlg.m_Text.GetLength() + 1);
    ASSERT(Briefing_screens[c_scr].effects[c_eff].text);

    if (Briefing_screens[c_scr].effects[c_eff].text) {
      strcpy(Briefing_screens[c_scr].effects[c_eff].text, dlg.m_Text.GetBuffer(1));
    }
  }
}

void CBriefEdit::OnBriefScreenAdd() {
  CBriefScreenEdit dlg;

  if (dlg.DoModal() == IDOK) {
    has_changed = true;
    int scr_to_add = -1;

    for (int i = 0; i < MAX_TELCOM_SCREENS; i++) {
      if (!Briefing_screens[i].used) {
        scr_to_add = i;
        break;
      }
    }
    if (scr_to_add == -1) {
      MessageBox("Out of Screens", "Error");
      return;
    }

    Briefing_screens[scr_to_add].used = true;
    strcpy(Briefing_screens[scr_to_add].layout, dlg.layout_str.GetBuffer(0));
    Briefing_screens[scr_to_add].mission_mask_set = dlg.m_Set;
    Briefing_screens[scr_to_add].mission_mask_unset = dlg.m_UnSet;

    if (Briefing_root_screen == -1) {
      Briefing_root_screen = scr_to_add;
      Briefing_screens[scr_to_add].prev = Briefing_screens[scr_to_add].next = -1;
    } else {
      int node = Briefing_root_screen;
      while (Briefing_screens[node].next != -1) {
        node = Briefing_screens[node].next;
      }
      Briefing_screens[node].next = scr_to_add;
      Briefing_screens[scr_to_add].prev = node;
      Briefing_screens[scr_to_add].next = -1;
    }
    CComboBox *combo = (CComboBox *)GetDlgItem(IDC_BRIEF_SCREEN_LIST);
    int sel = combo->AddString(dlg.m_sDesc);
    ASSERT(sel >= 0);
    combo->SetCurSel(sel);
    OnSelchangeBriefScreenList();
    UpdateLayoutBitmap();
    mprintf(0, "Added a screen\n");
  }
}

void CBriefEdit::OnBriefScreenDel() {
  UpdateData(true);
  int curr_screen;
  BriefEditGetCurScreenEffect(&curr_screen, NULL);
  if (curr_screen == -1) {
    MessageBox("No Screens To Delete", "Error");
    return;
  }

  if (MessageBox("Are You Sure You Want To Delete Screen?", "Confirmation", MB_YESNO) != IDYES)
    return;

  has_changed = true;

  int next, prev;

  ASSERT(curr_screen >= 0 && curr_screen < MAX_TELCOM_SCREENS);
  next = Briefing_screens[curr_screen].next;
  prev = Briefing_screens[curr_screen].prev;

  if (prev == -1) {
    Briefing_root_screen = next;
  } else {
    Briefing_screens[prev].next = next;
  }

  if (next != -1)
    Briefing_screens[next].prev = prev;

  // free the screen
  BriefEditFreeScreen(&Briefing_screens[curr_screen]);

  CComboBox *combo = (CComboBox *)GetDlgItem(IDC_BRIEF_SCREEN_LIST);
  combo->DeleteString(combo->GetCurSel());
  combo->SetCurSel(0);
  OnSelchangeBriefScreenList();
  UpdateData(false);
}

void CBriefEdit::OnBriefScreenEdit() {
  UpdateData(true);
  CComboBox *combo = (CComboBox *)GetDlgItem(IDC_BRIEF_SCREEN_LIST);
  int curr_screen = combo->GetCurSel();

  int scr_index;
  BriefEditGetCurScreenEffect(&scr_index, NULL);

  if (scr_index == -1) {
    MessageBox("No Screens To Edit", "Error");
    return;
  }

  CBriefScreenEdit dlg(scr_index);
  combo->GetLBText(curr_screen, dlg.m_sDesc);

  if (dlg.DoModal() == IDOK) {
    has_changed = true;
    // grab the information from the dialog
    combo->DeleteString(curr_screen);
    combo->InsertString(curr_screen, dlg.m_sDesc);
    combo->SetCurSel(curr_screen);

    strcpy(Briefing_screens[scr_index].layout, dlg.layout_str.GetBuffer(1));
    Briefing_screens[scr_index].mission_mask_set = dlg.m_Set;
    Briefing_screens[scr_index].mission_mask_unset = dlg.m_UnSet;
    UpdateLayoutBitmap();
  }
  UpdateData(false);
}

void CBriefEdit::UpdateInfo() {}

BOOL CBriefEdit::OnInitDialog() {
  CDialog::OnInitDialog();

  // Start the timer
  CWnd::SetTimer(1, 50, NULL);

  BriefEditInitScreens();

  UpdateInfo();
  has_changed = false;

  return TRUE;
}

void CBriefEdit::OnDestroy() {
  CDialog::OnDestroy();

  BriefEditFreeScreens();
}

void CBriefEdit::OnSelchangeBriefScreenList() {
  CComboBox *scr_combo = (CComboBox *)GetDlgItem(IDC_BRIEF_SCREEN_LIST);
  CComboBox *eff_combo = (CComboBox *)GetDlgItem(IDC_BRIEF_EFFECT_LIST);
  eff_combo->ResetContent();

  int curr_screen;

  BriefEditGetCurScreenEffect(&curr_screen, NULL);
  if (curr_screen == -1)
    return;

  // now go through the new screen and add effects
  int node = Briefing_screens[curr_screen].root_effect;
  tBriefScreen *bscr = &Briefing_screens[curr_screen];
  while (node != -1) {
    switch (bscr->effects[node].type) {
    case BE_TEXT:
    case BE_BMP:
    case BE_MOVIE:
    case BE_BKG:
    case BE_POLY:
    case BE_SND:
    case BE_BUTTON:
      eff_combo->AddString(bscr->effects[node].description);
      break;
    default:
      eff_combo->AddString("Unknown");
      break;
    }
    node = bscr->effects[node].next;
  }
  eff_combo->SetCurSel(0);

  UpdateLayoutBitmap();
}

void CBriefEdit::OnBriefSave() {
  UpdateData(true);
  char szFilter[] = "Descent3 Briefing Files (*.brf)|*.brf||";
  CFileDialog dlg(false, ".brf", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

  if (dlg.DoModal() == IDOK) {
    has_changed = false;
    m_GlobalValues.static_val = m_fStatic;
    m_GlobalValues.glitch_val = m_fGlitch;
    strcpy(m_GlobalValues.title, m_sTitle.GetBuffer(1));

    BriefEditSaveScreens(dlg.GetPathName().GetBuffer(1), (CComboBox *)GetDlgItem(IDC_BRIEF_SCREEN_LIST),
                         &m_GlobalValues);
  }
}

void CBriefEdit::OnLoad() {
  char szFilter[] = "Descent3 Briefing Files (*.brf)|*.brf||";
  CFileDialog dlg(true, ".brf", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter);

  if (dlg.DoModal() == IDOK) {
    CComboBox *combo = (CComboBox *)GetDlgItem(IDC_BRIEF_SCREEN_LIST);
    combo->ResetContent();
    BriefEditFreeScreens();
    BriefEditInitScreens();
    BriefEditLoadScreens(dlg.GetPathName().GetBuffer(1), combo, (CComboBox *)GetDlgItem(IDC_BRIEF_EFFECT_LIST),
                         &m_GlobalValues);

    m_fStatic = m_GlobalValues.static_val;
    m_fGlitch = m_GlobalValues.glitch_val;
    m_sTitle = m_GlobalValues.title;

    UpdateData(false);
    UpdateInfo();
    OnSelchangeBriefScreenList();
    UpdateLayoutBitmap();
    has_changed = false;
  }
}

void CBriefEdit::UpdateLayoutBitmap(void) {
  int scr;
  BriefEditGetCurScreenEffect(&scr, NULL);
  if (scr == -1)
    return;

  SetLayoutBitmap(Briefing_screens[scr].layout);
}

void CBriefEdit::SetLayoutBitmap(char *filename) {
  if (layout_bmp > BAD_BITMAP_HANDLE)
    bm_FreeBitmap(layout_bmp);

  layout_bmp = -1;

  if (filename[0] != '\0')
    layout_bmp = bm_AllocLoadFileBitmap(filename, 0);
  has_changed = true;
}

void CBriefEdit::ParseLayoutScreenFile(char *filename) {
  CFILE *file = cfopen(filename, "rt");
  if (!file)
    return;

  num_layouts = 0;
  if (layouts) {
    mem_free(layouts);
    layouts = NULL;
  }

  char buffer[512];

  cf_ReadString(buffer, 512, file);
  num_layouts = atoi(buffer);

  if (num_layouts <= 0) {
    cfclose(file);
    mprintf(0, "Zero or less Layout Screens in Layout File\n");
    return;
  }

  layouts = (tLayoutScreen *)mem_malloc(sizeof(tLayoutScreen) * num_layouts);
  if (!layouts) {
    mprintf(0, "Out of memory loading layout screens...trying to load %d screens\n", num_layouts);
    num_layouts = 0;
    cfclose(file);
    return;
  }

  memset(layouts, 0, sizeof(tLayoutScreen) * num_layouts);

  // format of a layout def.
  //--filename
  //--number of text boxes
  //--number of bmp boxes
  //----textbox defs
  //-----lx ty rx by
  //----bmp defs
  //-----x y

  for (int i = 0; i < num_layouts; i++) {
    // read filename
    cf_ReadString(layouts[i].filename, _MAX_PATH, file);

    // read num of text boxes
    cf_ReadString(buffer, 512, file);
    layouts[i].num_texts = atoi(buffer);
    ASSERT(layouts[i].num_texts >= 0 && layouts[i].num_texts < MAX_LAYOUT_PREDEFS);

    // read num of bmp boxes
    cf_ReadString(buffer, 512, file);
    layouts[i].num_bmps = atoi(buffer);
    ASSERT(layouts[i].num_bmps >= 0 && layouts[i].num_bmps < MAX_LAYOUT_PREDEFS);

    // read textbox defs
    for (int j = 0; j < layouts[i].num_texts; j++) {
      cf_ReadString(buffer, 512, file);

      // now parse to pull out the individual values
      char *lxp, *rxp, *typ, *byp;
      lxp = rxp = typ = byp = NULL;

      char *p = buffer;

      while ((*p) && (*p == ' '))
        p++;
      lxp = p;
      while ((*p) && (*p != ' '))
        p++;
      *p = '\0';
      p++;
      while ((*p) && (*p == ' '))
        p++;
      typ = p;
      while ((*p) && (*p != ' '))
        p++;
      *p = '\0';
      p++;
      while ((*p) && (*p == ' '))
        p++;
      rxp = p;
      while ((*p) && (*p != ' '))
        p++;
      *p = '\0';
      p++;
      while ((*p) && (*p == ' '))
        p++;
      byp = p;

      ASSERT((*lxp != 0) && (*rxp != 0) && (*typ != 0) && (*byp != 0));
      layouts[i].texts[j].lx = atoi(lxp);
      layouts[i].texts[j].rx = atoi(rxp);
      layouts[i].texts[j].ty = atoi(typ);
      layouts[i].texts[j].by = atoi(byp);
    }

    // read bmp defs
    for (int j = 0; j < layouts[i].num_bmps; j++) {
      cf_ReadString(buffer, 512, file);

      // now parse to pull out the individual values
      char *xp, *yp;
      xp = yp = NULL;

      char *p = buffer;

      while ((*p) && (*p == ' '))
        p++;
      xp = p;
      while ((*p) && (*p != ' '))
        p++;
      *p = '\0';
      p++;
      while ((*p) && (*p == ' '))
        p++;
      yp = p;

      ASSERT((*xp != 0) && (*yp != 0));
      layouts[i].bmps[j].x = atoi(xp);
      layouts[i].bmps[j].y = atoi(yp);
    }
  }
  cfclose(file);
}

int bmw, bmh;

void CBriefEdit::DrawRect(ddgr_color color, int lx, int ty, int rx, int by, grViewport *vport) {
  if (lx < 0)
    lx = 0;
  if (lx > (bmw - 1))
    lx = bmw - 1;
  if (rx < 0)
    rx = 0;
  if (rx > (bmw - 1))
    rx = bmw - 1;
  if (ty < 0)
    ty = 0;
  if (ty > (bmh - 1))
    ty = bmh - 1;
  if (by < 0)
    by = 0;
  if (by > (bmh - 1))
    by = bmh - 1;

  // vport->fillrect(color,lx,ty,rx,by);
  vport->line(color, lx, ty, lx, by);
  vport->line(color, rx, ty, rx, by);
  vport->line(color, lx, ty, rx, ty);
  vport->line(color, lx, by, rx, by);
}

void CBriefEdit::UpdateView(void) {
  CWnd *objwnd;
  RECT rect;
  int x, y, w, h;

  objwnd = GetDlgItem(IDC_BRIEF_PICTURE);
  objwnd->GetWindowRect(&rect);
  ScreenToClient(&rect);

  if (layout_bmp > BAD_BITMAP_HANDLE) {
    bmw = bm_w(layout_bmp, 0);
    bmh = bm_h(layout_bmp, 0);
  } else {
    bmw = 640;
    bmh = 480;
  }

  static float age = 0;
  static bool on = false;
  static float last_time = 0;

  float t = timer_GetTime();
  float frametime = t - last_time;
  last_time = t;

  age += frametime;

  if (age > 0.5) {
    on = !on;
    age = 0;
  }

  rend_StartFrame(0, 0, bmw, bmh);

  Desktop_surf->attach_to_window((unsigned)m_hWnd);

  w = rect.right - rect.left;
  h = rect.bottom - rect.top;

  static bool first_call = true;

  if (first_call)
    Desktop_surf->clear(rect.left, rect.top, w, h);

  m_ObjectSurf.create(bmw, bmh, BPP_16);

  if (layout_bmp > BAD_BITMAP_HANDLE) {
    m_ObjectSurf.load(layout_bmp);
  } else
    Desktop_surf->clear(rect.left, rect.top, w, h);

  grViewport *vport = new grViewport(&m_ObjectSurf);
  vport->lock();

  // now we need to go through all the effects in the screen and draw a rep of em
  int curr_screen, curr_effect;
  int node;
  tBriefEffect *effects;
  BriefEditGetCurScreenEffect(&curr_screen, &curr_effect);

  if (curr_screen != -1) {
    node = Briefing_screens[curr_screen].root_effect;
    effects = Briefing_screens[curr_screen].effects;

    while (node != -1) {
      if (node == curr_effect && !on) {
      } else {
        switch (effects[node].type) {
        case BE_TEXT:
          DrawRect(GR_RGB(255, 40, 255), effects[node].text_desc.textbox.left, effects[node].text_desc.textbox.top,
                   effects[node].text_desc.textbox.right, effects[node].text_desc.textbox.bottom, vport);
          break;
        case BE_BMP: {
          if (effects[node].w == -1) {
            // we need to set up values
            int handle = bm_AllocLoadFileBitmap(effects[node].bmp_desc.filename, 0);
            if (handle > BAD_BITMAP_HANDLE) {
              effects[node].w = bm_w(handle, 0);
              effects[node].h = bm_h(handle, 0);
              bm_FreeBitmap(handle);
            } else {
              effects[node].w = effects[node].h = 16;
            }
          }
          int x, y, w, h;
          x = effects[node].bmp_desc.x;
          y = effects[node].bmp_desc.y;
          w = effects[node].w - 1;
          h = effects[node].h - 1;
          DrawRect(GR_RGB(40, 255, 40), x, y, x + w, y + h, vport);
        } break;
        case BE_MOVIE:
          break;
        case BE_BKG:
          break;
        case BE_POLY:
          break;
        case BE_BUTTON:
          if (effects[node].w == -1) {
            // we need to set up values
            int handle = bm_AllocLoadFileBitmap(effects[node].button_desc.filename, 0);
            if (handle > BAD_BITMAP_HANDLE) {
              effects[node].w = bm_w(handle, 0);
              effects[node].h = bm_h(handle, 0);
              bm_FreeBitmap(handle);
            } else {
              effects[node].w = effects[node].h = 16;
            }
          }
          int x, y, w, h;
          x = effects[node].button_desc.x;
          y = effects[node].button_desc.y;
          w = effects[node].w - 1;
          h = effects[node].h - 1;
          DrawRect(GR_RGB(255, 255, 40), x, y, x + w, y + h, vport);
          break;
        }
      }
      node = effects[node].next;
    }
  }

  vport->unlock();
  x = rect.left + (w / 2) - m_ObjectSurf.width() / 2;
  y = rect.top + (h / 2) - m_ObjectSurf.height() / 2;

  Desktop_surf->blt(x, y, &m_ObjectSurf);

  rend_EndFrame();

  delete vport;
  m_ObjectSurf.free();
  Desktop_surf->attach_to_window((unsigned)NULL);

  if (first_call)
    first_call = false;
}

void CBriefEdit::OnTimer(UINT nIDEvent) {
  UpdateView();
  CDialog::OnTimer(nIDEvent);
}

void CBriefEdit::OnManage() {
  CBriefManage dlg;
  dlg.DoModal();
}
