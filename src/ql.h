//
// ql.h
//   Query Language Component Interface
//

// This file only gives the stub for the QL component

#ifndef QL_H
#define QL_H

#include <stdlib.h>
#include <string.h>
#include "redbase.h"
#include "parser.h"
#include "ql_error.h"
#include "rm.h"
#include "ix.h"
#include "sm.h"
#include "iterator.h"

//
// QL_Manager: query language (DML)
//
class QL_Manager {
 public:
  QL_Manager (SM_Manager &smm, IX_Manager &ixm, RM_Manager &rmm);
  ~QL_Manager();                               // Destructor

  RC Select  (int nSelAttrs,                   // # attrs in select clause
              const RelAttr selAttrs[],        // attrs in select clause
              int   nRelations,                // # relations in from clause
              const char * const relations[],  // relations in from clause
              int   nConditions,               // # conditions in where clause
              const Condition conditions[]);   // conditions in where clause

  RC Insert  (const char *relName,             // relation to insert into
              int   nValues,                   // # values
              const Value values[]);           // values to insert

  RC Delete  (const char *relName,             // relation to delete from
              int   nConditions,               // # conditions in where clause
              const Condition conditions[]);   // conditions in where clause

  RC Update  (const char *relName,             // relation to update
              const RelAttr &updAttr,          // attribute to update
              const int bIsValue,              // 1 if RHS is a value, 0 if attr
              const RelAttr &rhsRelAttr,       // attr on RHS to set LHS eq to
              const Value &rhsValue,           // or value to set attr eq to
              int   nConditions,               // # conditions in where clause
              const Condition conditions[]);   // conditions in where clause
 public:
  RC IsValid() const;
  // Choose between filescan and indexscan for first operation - leaf level of
  // operator tree
  Iterator* GetLeafIterator(const char *relName_,
                            int nConditions, const Condition conditions_[]);

 private:
  RM_Manager& rmm;
  IX_Manager& ixm;
  SM_Manager& smm;
};

#endif // QL_H
