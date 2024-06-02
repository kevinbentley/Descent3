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

 * $Logfile: /DescentIII/Main/lib/psclass.h $
 * $Revision: 8 $
 * $Date: 4/16/99 4:26a $
 * $Author: Jeff $
 *
 * New Class Library
 *
 * $Log: /DescentIII/Main/lib/psclass.h $
 *
 * 8     4/16/99 4:26a Jeff
 * removed ifdef of linux since new compiler compiles it
 *
 * 7     4/15/99 1:44a Jeff
 * changes for linux compile
 *
 * 6     12/16/98 1:57p Samir
 * Replaced CleanupString2 with CleanupStr
 *
 * 5     10/02/98 11:16a Jeff
 * removed 'struct' from the template, generates an error in VC6 that
 * keeps it from compiling
 *
 * 4     9/17/98 7:05p Samir
 * added string token class.
 *
 * 3     7/28/98 5:42p Samir
 * added queue class.
 *
 * 2     7/23/98 11:36a Samir
 * Added class library header.
 *
 * $NoKeywords: $
 */

#ifndef PSCLASS_H
#define PSCLASS_H

#include <cstdint>
#include <cstddef>

//	a universal list node to use with the list type
template <class T> struct tListNode {
  T t;
  tListNode<T> *next;
};

//	LIST CLASSES
//

//	tList
//		this is a VERY BASIC list class that encapsulates a lot
//		of list operations into one class.  this class handles list NODES ONLY.
//		a more advanced form is to come, but this is for those hardcode programmers.

//	to declare say, a list that will contain integers, do this:
//		tList<int> list;
//		tListNode<int> *node;
//		node = new tListNode<int>;
//		node->data = 1;
//		list.Link(node);
//		it is the programmers responsibility to create the nodes DYNAMICALLY

//	universal single-linked-list type
template <class T> class tList {
  tListNode<T> *m_link, *m_mark;
  int m_length;

public:
  tList() {
    m_link = m_mark = NULL;
    m_length = 0;
  };
  ~tList() { tList::free(); };

  //	moves to start of list. used for iteration
  tListNode<T> *start() {
    m_mark = m_link;
    return m_mark;
  }

  //	gets next list item in iteration.  if at end of list, last item will be returned.
  tListNode<T> *next() {
    m_mark = (m_mark->next) ? m_mark->next : m_mark;
    return get();
  };

  //	returns the node at the current link location in iteration.
  tListNode<T> *get() const { return m_mark ? m_mark : NULL; };

  //	length
  int length() const { return m_length; };

  //	frees list
  void free() {
    m_link = m_mark = NULL;
    m_length = 0;
  };

  //	make a link at the current mark location.
  void link(tListNode<T> *node) {
    if (m_link) {
      node->next = m_mark->next;
      m_mark->next = node;
    } else {
      m_link = node;
      node->next = NULL;
    }
    m_mark = node;
    m_length++;
  };

  //	unlink a node on the list at the current mark, returning the unlinked node.
  tListNode<T> *unlink() {
    tListNode<T> *freenode, *node;
    if (!m_link)
      return NULL;
    if (m_link == m_mark) {
      freenode = m_mark;
      m_mark = m_link = m_link->next;
    } else {
      node = m_link;
      while (node->next != m_mark)
        node = node->next;
      freenode = m_mark;
      node->next = m_mark->next;
    }
    freenode->next = NULL;
    return freenode;
  };
};

//	tQueue
//		a circular queue implementation

template <class T, int t_LEN> class tQueue {
  T m_items[t_LEN];
  int16_t m_head, m_tail;

public:
  tQueue() { m_head = m_tail = 0; };
  ~tQueue(){};

  void send(T &item) { // sends an item onto the queue
    int16_t temp = m_tail + 1;
    if (temp == t_LEN)
      temp = 0;
    if (temp != m_head) {
      m_items[m_tail] = item;
      m_tail = temp;
    }
  };
  bool recv(T *item) { // returns an item from the queue, false if no item.
    if (m_head == m_tail)
      return false;
    *item = m_items[m_head++];
    if (m_head == t_LEN)
      m_head = 0;
    return true;
  };

  void flush() { // flush queue entries.
    m_head = m_tail = 0;
  };
};

#endif
