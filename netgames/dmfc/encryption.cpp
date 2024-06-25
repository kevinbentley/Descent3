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

--- HISTORICAL COMMENTS FOLLOW ---

 * $Logfile: /DescentIII/Main/dmfc/encryption.cpp $
 * $Revision: 1.1.1.1 $
 * $Date: 2003/08/26 03:57:21 $
 * $Author: kevinb $
 *
 * header file for ICE encryption class
 *
 * $Log: encryption.cpp,v $
 * Revision 1.1.1.1  2003/08/26 03:57:21  kevinb
 * initial 1.5 import
 *
 *
 * 2     7/08/99 2:37a Jeff
 * created encryption class based off of ICE encryption
 *
 * $NoKeywords: $
 */

#include "encryption.h"

class IceSubkey {
public:
  uint32_t val[3];
};

// the S-boxes
static uint32_t ice_sbox[4][1024];
static int ice_sboxes_initialised = 0;

// modulo values for the S-boxes
static const int ice_smod[4][4] = {
    {333, 313, 505, 369}, {379, 375, 319, 391}, {361, 445, 451, 397}, {397, 425, 395, 505}};

// XOR values for the S-boxes
static const int ice_sxor[4][4] = {
    {0x83, 0x85, 0x9b, 0xcd}, {0xcc, 0xa7, 0xad, 0x41}, {0x4b, 0x2e, 0xd4, 0x33}, {0xea, 0xcb, 0x2e, 0x04}};

// Permutation values for the P-box
static const uint32_t ice_pbox[32] = {
    0x00000001, 0x00000080, 0x00000400, 0x00002000, 0x00080000, 0x00200000, 0x01000000, 0x40000000,
    0x00000008, 0x00000020, 0x00000100, 0x00004000, 0x00010000, 0x00800000, 0x04000000, 0x20000000,
    0x00000004, 0x00000010, 0x00000200, 0x00008000, 0x00020000, 0x00400000, 0x08000000, 0x10000000,
    0x00000002, 0x00000040, 0x00000800, 0x00001000, 0x00040000, 0x00100000, 0x02000000, 0x80000000};

// key rotation schedule
static constexpr int ice_keyrot[16] = {0, 1, 2, 3, 2, 1, 3, 0, 1, 3, 2, 0, 3, 1, 0, 2};

//
// 8-bit Galois Field multiplication of a by b, modulo m.
// Just like arithmetic multiplication, except that additions and
// subtractions are replaced by XOR.
//
static uint32_t gf_mult(uint32_t a, uint32_t b, uint32_t m) {
  uint32_t res = 0;

  while (b) {
    if (b & 1)
      res ^= a;

    a <<= 1;
    b >>= 1;

    if (a >= 256)
      a ^= m;
  }

  return (res);
}

//
// Galois Field exponentiation.
// Raise the base to the power of 7, modulo m.
//
static uint32_t gf_exp7(uint32_t b, uint32_t m) {
  uint32_t x;

  if (b == 0)
    return 0;

  x = gf_mult(b, b, m);
  x = gf_mult(b, x, m);
  x = gf_mult(x, x, m);

  return (gf_mult(b, x, m));
}

//
// Carry out the ICE 32-bit P-box permutation.
//
static uint32_t ice_perm32(uint32_t x) {
  uint32_t res = 0;
  const uint32_t *pbox = ice_pbox;

  while (x) {
    if (x & 1)
      res |= *pbox;
    pbox++;
    x >>= 1;
  }

  return (res);
}

//
// Initialise the ICE S-boxes.
// This only has to be done once.
//
static void ice_sboxes_init(void) {
  int i;

  for (i = 0; i < 1024; i++) {
    int col = (i >> 1) & 0xff;
    int row = (i & 0x1) | ((i & 0x200) >> 8);
    uint32_t x;

    x = gf_exp7(col ^ ice_sxor[0][row], ice_smod[0][row]) << 24;
    ice_sbox[0][i] = ice_perm32(x);

    x = gf_exp7(col ^ ice_sxor[1][row], ice_smod[1][row]) << 16;
    ice_sbox[1][i] = ice_perm32(x);

    x = gf_exp7(col ^ ice_sxor[2][row], ice_smod[2][row]) << 8;
    ice_sbox[2][i] = ice_perm32(x);

    x = gf_exp7(col ^ ice_sxor[3][row], ice_smod[3][row]);
    ice_sbox[3][i] = ice_perm32(x);
  }
}

//
// Create a new ICE key.
//
IceKey::IceKey(int n) {
  if (!ice_sboxes_initialised) {
    ice_sboxes_init();
    ice_sboxes_initialised = 1;
  }

  if (n < 1) {
    _size = 1;
    _rounds = 8;
  } else {
    _size = n;
    _rounds = n * 16;
  }

  _keysched = new IceSubkey[_rounds];
}

//
// Destroy an ICE key.
//
IceKey::~IceKey() {
  int i, j;

  for (i = 0; i < _rounds; i++) {
    for (j = 0; j < 3; j++) {
      _keysched[i].val[j] = 0;
    }
  }

  _rounds = _size = 0;

  delete[] _keysched;
}

//
// The single round ICE f function.
//
static uint32_t ice_f(uint32_t p, const IceSubkey *sk) {
  uint32_t tl, tr; /* Expanded 40-bit values */
  uint32_t al, ar; /* Salted expanded 40-bit values */

  // Left half expansion
  tl = ((p >> 16) & 0x3ff) | (((p >> 14) | (p << 18)) & 0xffc00);

  // Right half expansion
  tr = (p & 0x3ff) | ((p << 2) & 0xffc00);

  // Perform the salt permutation
  al = sk->val[2] & (tl ^ tr);
  ar = al ^ tr;
  al ^= tl;

  al ^= sk->val[0]; // XOR with the subkey
  ar ^= sk->val[1];

  // S-box lookup and permutation
  return (ice_sbox[0][al >> 10] | ice_sbox[1][al & 0x3ff] | ice_sbox[2][ar >> 10] | ice_sbox[3][ar & 0x3ff]);
}

//
// Encrypt a block of 8 bytes of data with the given ICE key.
//
void IceKey::encrypt(const uint8_t *ptext, uint8_t *ctext) const {
  int i;
  uint32_t l, r;

  l = (((uint32_t)ptext[0]) << 24) | (((uint32_t)ptext[1]) << 16) | (((uint32_t)ptext[2]) << 8) |
      ptext[3];

  r = (((uint32_t)ptext[4]) << 24) | (((uint32_t)ptext[5]) << 16) | (((uint32_t)ptext[6]) << 8) |
      ptext[7];

  for (i = 0; i < _rounds; i += 2) {
    l ^= ice_f(r, &_keysched[i]);
    r ^= ice_f(l, &_keysched[i + 1]);
  }

  for (i = 0; i < 4; i++) {
    ctext[3 - i] = (uint8_t)r & 0xff;
    ctext[7 - i] = (uint8_t)l & 0xff;

    r >>= 8;
    l >>= 8;
  }
}

//
// Decrypt a block of 8 bytes of data with the given ICE key.
//
void IceKey::decrypt(const uint8_t *ctext, uint8_t *ptext) const {
  int i;
  uint32_t l, r;

  l = (((uint32_t)ctext[0]) << 24) | (((uint32_t)ctext[1]) << 16) | (((uint32_t)ctext[2]) << 8) |
      ctext[3];
  r = (((uint32_t)ctext[4]) << 24) | (((uint32_t)ctext[5]) << 16) | (((uint32_t)ctext[6]) << 8) |
      ctext[7];

  for (i = _rounds - 1; i > 0; i -= 2) {
    l ^= ice_f(r, &_keysched[i]);
    r ^= ice_f(l, &_keysched[i - 1]);
  }

  for (i = 0; i < 4; i++) {
    ptext[3 - i] = (uint8_t)r & 0xff;
    ptext[7 - i] = (uint8_t)l & 0xff;

    r >>= 8;
    l >>= 8;
  }
}

//
// Set 8 rounds [n, n+7] of the key schedule of an ICE key.
//
void IceKey::scheduleBuild(uint16_t *kb, int n, const int *keyrot) {
  int i;

  for (i = 0; i < 8; i++) {
    int j;
    int kr = keyrot[i];
    IceSubkey *isk = &_keysched[n + i];

    for (j = 0; j < 3; j++)
      isk->val[j] = 0;

    for (j = 0; j < 15; j++) {
      int k;
      uint32_t *curr_sk = &isk->val[j % 3];

      for (k = 0; k < 4; k++) {
        uint16_t *curr_kb = &kb[(kr + k) & 3];
        int bit = *curr_kb & 1;

        *curr_sk = (*curr_sk << 1) | bit;
        *curr_kb = (*curr_kb >> 1) | ((bit ^ 1) << 15);
      }
    }
  }
}

//
// Set the key schedule of an ICE key.
//
void IceKey::set(const uint8_t *key) {
  int i;

  if (_rounds == 8) {
    uint16_t kb[4];

    for (i = 0; i < 4; i++) {
      kb[3 - i] = (key[i * 2] << 8) | key[i * 2 + 1];
    }

    scheduleBuild(kb, 0, ice_keyrot);
    return;
  }

  for (i = 0; i < _size; i++) {
    int j;
    uint16_t kb[4];

    for (j = 0; j < 4; j++) {
      kb[3 - j] = (key[i * 8 + j * 2] << 8) | key[i * 8 + j * 2 + 1];

      scheduleBuild(kb, i * 8, ice_keyrot);
      scheduleBuild(kb, _rounds - 8 - i * 8, &ice_keyrot[8]);
    }
  }
}

//
// Return the key size, in bytes.
//
int IceKey::keySize(void) const { return (_size * 8); }

//
// Return the block size, in bytes.
//
int IceKey::blockSize(void) const { return 8; }
