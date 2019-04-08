//
//  Exception.h
//
//  Author:     Gene Ryu
//  Created:    2019. 04. 08. 17:32
//  Copyright (c) 2019 Gene Ryu. All rights reserved.
//

/// \file
/// \brief  Base exceptions.
#ifndef _PR_EXCEPTION_H
#define _PR_EXCEPTION_H

#include <stdexcept>
#include <exception>

namespace pr {

class Exception : public std::exception {
public:
    // Exception();
    const char* what() const noexcept
    {
        return "Exception";
    }
};

} // namespace pr

#endif /* _PR_EXCEPTION_H */
