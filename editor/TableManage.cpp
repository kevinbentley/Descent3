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

#include "stdafx.h"
#include "resource.h"
#include "TableFileEdit.h"

#include "PsTypes.h"
// #include "descent.h"
#include "TableManage.h"
#include "manage.h"
// #include "pserror.h"
// #include "gametexture.h"
// #include "texpage.h"
// #include "doorpage.h"
// #include "soundpage.h"
// #include "megapage.h"
// #include "shippage.h"
// #include "weaponpage.h"
// #include "gamefilepage.h"
#include "mono.h"
#include "genericpage.h"
// #include "object.h"
// #include "ddio.h"
#include "cfile.h"
// #include "AppDatabase.h"
#include "mem.h"

////////////////////////////////////////////////////////////////
// GenericPageNode Class Members
////////////////////////////////////////////////////////////////
GenericPageNode::GenericPageNode() {
  prev = NULL;
  next = NULL;
  page_id = 0;
}

GenericPageNode::~GenericPageNode() {
  // Free up the object description memory
  if (genericpage.objinfo_struct.description != NULL) {
    mem_free(genericpage.objinfo_struct.description);
    genericpage.objinfo_struct.description = NULL;
  }
}

bool GenericPageNode::operator<(const GenericPageNode &node) {
  return (stricmp(genericpage.objinfo_struct.name, node.genericpage.objinfo_struct.name) < 0);
}

////////////////////////////////////////////////////////////////
// GenericPageList Class Members
////////////////////////////////////////////////////////////////
GenericPageList::GenericPageList() {
  m_head = NULL;
  m_tail = NULL;
  m_size = 0;
  m_TableFilename = "";
  m_TableLoaded = FALSE;
  m_TableModified = FALSE;
  m_SelectedNode = NULL;
  m_SelectedIndex = 0;
}

GenericPageList::~GenericPageList() { ClearList(); }

void GenericPageList::ClearList(void) {
  GenericPageNode *temp, *node;

  node = m_head;
  while (node != NULL) {
    temp = node;
    node = node->next;
    delete temp;
  }
  m_size = 0;
  m_head = NULL;
  m_tail = NULL;
  m_TableFilename = "";
  m_TableLoaded = FALSE;
  m_TableModified = FALSE;
  m_SelectedNode = NULL;
  m_SelectedIndex = 0;
}

// Adds the node to the list in ascending alphabetical order
// according to the page names of the nodes
bool GenericPageList::AddToList(GenericPageNode *new_node) {
  GenericPageNode *node;

  if (new_node == NULL)
    return FALSE;

  // Handle empty list case
  if (m_head == NULL) {
    m_head = new_node;
    m_tail = new_node;
    new_node->next = NULL;
    new_node->prev = NULL;

    m_size++;
    return TRUE;
  }

  // Handle (new node < list head) case
  if ((*new_node) < (*m_head)) {
    new_node->next = m_head;
    new_node->prev = NULL;
    m_head->prev = new_node;
    m_head = new_node;

    m_size++;
    return TRUE;
  }

  // Search through list until end of list or until the new node is less
  // than the next node, then add the new node after the current node
  node = m_head;
  while (node->next != NULL && (*(node->next)) < (*new_node))
    node = node->next;

  new_node->next = node->next;
  new_node->prev = node;

  if (node->next == NULL)
    m_tail = new_node;
  else
    node->next->prev = new_node;

  node->next = new_node;

  m_size++;

  return TRUE;
}

bool GenericPageList::LoadTable(char *table_filename) {
  CFILE *infile;
  uint8_t pagetype;
  int done;
  uint32_t page_id;

  GenericPageNode *generic_page_node;

  infile = cfopen(table_filename, "rb");

  if (!infile) {
    // mprintf(0,"Couldn't open table file to reorder!\n");
    // Int3();
    return FALSE;
  }

  CWaitCursor wc;

  // Wipeout the list first
  ClearList();

  done = 0;
  page_id = 0;

  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    pagetype = cf_ReadByte(infile);

    // If not a generic page, just read it in and ignore it
    if (pagetype != PAGETYPE_GENERIC) {
      mng_ReadDummyPage(infile, pagetype);
      page_id++;
      continue;
    }

    generic_page_node = new GenericPageNode;
    if (generic_page_node == NULL) {
      return FALSE;
    }
    mng_ReadNewGenericPage(infile, &(generic_page_node->genericpage));
    generic_page_node->page_id = page_id;
    AddToList(generic_page_node);

    page_id++;
  }

  cfclose(infile);

  // Set Loaded tabel data
  m_TableFilename = table_filename;
  m_TableLoaded = TRUE;

  m_TableModified = FALSE;

  return TRUE;
}

bool GenericPageList::SaveTable(char *table_filename) {
  CFILE *infile, *outfile;
  uint8_t pagetype, replaced = 0;
  int done = 0;
  uint32_t page_id;
  GenericPageNode *new_generic_page;
  mngs_generic_page genericpage;

  CWaitCursor wc;

  // If no table is loaded, get outta here
  if (!m_TableLoaded)
    return FALSE;

  // First make sure we can open the table file and the temp table file
  infile = cfopen(m_TableFilename.GetBuffer(0), "rb");
  if (!infile) {
    mprintf(0, "Couldn't open table file to replace generic!\n");
    return FALSE;
  }

  outfile = cfopen(TEMP_TABLE_FILENAME, "wb");
  if (!outfile) {
    mprintf(0, "Couldn't open temp table file to replace generic!\n");
    cfclose(infile);
    return FALSE;
  }

  // Clear out the generic page
  memset(&genericpage, 0, sizeof(mngs_generic_page));

  // Read through the entire pagefile and replace the page we want replaced
  // If we can't find the one we want, we simply append it to the end of the file
  page_id = 0;
  while (!done) {
    if (cfeof(infile)) {
      done = 1;
      continue;
    }
    pagetype = cf_ReadByte(infile);

    // If not a generic page, just read it in and write it right back out
    if (pagetype != PAGETYPE_GENERIC) {
      mng_ReadWriteDummyPage(infile, outfile, pagetype);
      page_id++;
      continue;
    }

    mng_ReadNewGenericPage(infile, &genericpage);

    // Look for the generic page with the current page position in list
    new_generic_page = FindNode(page_id);
    if (new_generic_page == NULL) {
      // There is a page incompatibility!!!!
      // so, just write out the one that was read instead
      mng_WriteNewGenericPage(outfile, &genericpage);
      OutrageMessageBox("File incompatibility Error!", "Error!");
    } else {
      // Found the page for this position in the list,
      // So write out the new generic page
      mng_WriteNewGenericPage(outfile, &(new_generic_page->genericpage));
    }

    // Free up the description memory for the temp page
    if (genericpage.objinfo_struct.description != NULL) {
      mem_free(genericpage.objinfo_struct.description);
      genericpage.objinfo_struct.description = NULL;
    }

    page_id++;
  }

  cfclose(infile);
  cfclose(outfile);

  if (table_filename == NULL)
    // if no filename specified, just save it to the currently loaded file
    table_filename = m_TableFilename.GetBuffer(0);
  else {
    // We need to create this one just so it can get deleted alright by
    // Jason's Switcheroo function
    outfile = cfopen(table_filename, "wb");
    if (!outfile)
      return FALSE;
    cfclose(outfile);
  }

  // Now, perform the switcheroo by deleting the real table file and renaming the
  // temp table file to be the new "real" table file.
  if (!SwitcherooFiles(table_filename, TEMP_TABLE_FILENAME))
    return FALSE;

  m_TableModified = FALSE;
  m_TableFilename = table_filename;

  return TRUE; // successful!
}

bool GenericPageList::FillFromList(CComboBox *list) {
  GenericPageNode *node;

  list->ResetContent();

  node = m_head;
  while (node != NULL) {
    list->InsertString(-1, node->genericpage.objinfo_struct.name);
    node = node->next;
  }

  // Select the start of the list
  SelectNode(0);

  return TRUE;
}

void GenericPageList::SelectNext(void) {
  if (m_SelectedNode == NULL)
    return;

  if (m_SelectedNode->next == NULL) {
    m_SelectedNode = m_head;
    m_SelectedIndex = 0;
  } else {
    m_SelectedNode = m_SelectedNode->next;
    m_SelectedIndex++;
  }
}

void GenericPageList::SelectPrev(void) {
  if (m_SelectedNode == NULL)
    return;

  if (m_SelectedNode->prev == NULL) {
    m_SelectedNode = m_tail;
    m_SelectedIndex = (m_size - 1);
  } else {
    m_SelectedNode = m_SelectedNode->prev;
    m_SelectedIndex--;
  }
}

void GenericPageList::SelectNode(uint32_t list_index) {
  uint32_t j;
  GenericPageNode *node;

  if (list_index < 0 || list_index > (m_size - 1))
    return;

  node = m_head;
  for (j = 0; j < list_index; j++)
    if (node != NULL)
      node = node->next;

  m_SelectedNode = node;
  m_SelectedIndex = list_index;
}

void GenericPageList::DisplaySelected(CComboBox *list, CEdit *description) {
  char *text;

  if (m_SelectedNode == NULL)
    return;

  list->SetCurSel(m_SelectedIndex);

  text = m_SelectedNode->genericpage.objinfo_struct.description;
  if (text == NULL)
    description->SetWindowText(NO_DESCRIPTION_STRING);
  else
    description->SetWindowText(text);
}

void GenericPageList::SaveSelected(CEdit *description) {
  CString new_descrip;
  char *new_text;
  char *old_text;

  if (m_SelectedNode == NULL)
    return;

  // Get pointer to old text
  old_text = m_SelectedNode->genericpage.objinfo_struct.description;

  // Get Copy of new Description text
  description->GetWindowText(new_descrip);
  new_text = (char *)mem_malloc(strlen(new_descrip.GetBuffer(0)) + 1);
  ASSERT(new_text); // out of memory!
  sprintf(new_text, "%s", new_descrip.GetBuffer(0));

  // Check if new description is empty, if it is, make it NULL
  if (strlen(new_text) == 0 || stricmp(new_text, NO_DESCRIPTION_STRING) == 0) {
    mem_free(new_text);
    new_text = NULL;
  }

  // If both new and old are empty, get outta here
  if (old_text == NULL && new_text == NULL) {
    mem_free(new_text);
    return;
  }

  // If both have descriptions and they match, get outta here
  if (old_text != NULL && new_text != NULL) {
    if (strcmp(old_text, new_text) == 0) {
      mem_free(new_text);
      return;
    }
  }

  // Free up the old text memory, and assign it to the new text
  if (old_text != NULL)
    mem_free(old_text);

  m_SelectedNode->genericpage.objinfo_struct.description = new_text;
  m_TableModified = TRUE;

  return;
}

GenericPageNode *GenericPageList::FindNode(uint32_t page_id) {
  GenericPageNode *node, *found_node;

  found_node = NULL;
  node = m_head;
  while (node != NULL) {
    if (node->page_id == page_id) {
      found_node = node;
      break;
    }
    node = node->next;
  }

  return (found_node);
}

int GenericPageList::ModifiedPrompt(CDialog *wnd) {
  // If current file has been modified, check with user first...
  if (!m_TableModified)
    return (IDYES);
  if (wnd->MessageBox("Changes to table file will be lost. Proceed?", "Table File Has Been Modified", MB_YESNO) ==
      IDYES)
    return (IDYES);
  return (IDNO);
}

void GenericPageList::SetTitleString(CDialog *wnd) {
  char title[1024];
  char loaded_file[1024];

  if (m_TableLoaded)
    sprintf(loaded_file, " - [%s%s]", m_TableFilename.GetBuffer(0), (m_TableModified) ? "*" : "");
  else
    sprintf(loaded_file, "");

  sprintf(title, "%s%s", TITLE_NAME, loaded_file);
  wnd->SetWindowText(title);
}
