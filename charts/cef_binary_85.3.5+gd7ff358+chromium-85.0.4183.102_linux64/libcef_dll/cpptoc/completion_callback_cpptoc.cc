// Copyright (c) 2020 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=ce5faec2604b151f3872baae02247038c41dfbbd$
//

#include "libcef_dll/cpptoc/completion_callback_cpptoc.h"
#include "libcef_dll/shutdown_checker.h"

namespace {

// MEMBER FUNCTIONS - Body may be edited by hand.

void CEF_CALLBACK
completion_callback_on_complete(struct _cef_completion_callback_t* self) {
  shutdown_checker::AssertNotShutdown();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefCompletionCallbackCppToC::Get(self)->OnComplete();
}

}  // namespace

// CONSTRUCTOR - Do not edit by hand.

CefCompletionCallbackCppToC::CefCompletionCallbackCppToC() {
  GetStruct()->on_complete = completion_callback_on_complete;
}

// DESTRUCTOR - Do not edit by hand.

CefCompletionCallbackCppToC::~CefCompletionCallbackCppToC() {
  shutdown_checker::AssertNotShutdown();
}

template <>
CefRefPtr<CefCompletionCallback> CefCppToCRefCounted<
    CefCompletionCallbackCppToC,
    CefCompletionCallback,
    cef_completion_callback_t>::UnwrapDerived(CefWrapperType type,
                                              cef_completion_callback_t* s) {
  NOTREACHED() << "Unexpected class type: " << type;
  return nullptr;
}

template <>
CefWrapperType CefCppToCRefCounted<CefCompletionCallbackCppToC,
                                   CefCompletionCallback,
                                   cef_completion_callback_t>::kWrapperType =
    WT_COMPLETION_CALLBACK;
