//
//  Base.h
//
//  Author:     Gene Ryu
//  Created:    2019. 04. 06. 18:38
//  Copyright (c) 2019 Gene Ryu. All rights reserved.
//

/// \file
/// \brief  Primer base.
#ifndef _PR_BASE_H
#define _PR_BASE_H

namespace pr {

class Base {
private:
public:
    operator const char*() const
    {
        return "<Primer object>";
    }

};


template <typename T>
class Optional {

};


} // namespace pr

#endif /* _PR_BASE_H */
