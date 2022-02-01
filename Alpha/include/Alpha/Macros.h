#pragma once

#ifndef MACROS_H
#define MACROS_H

#include <memory>

#define DEF_SMART_POINTER(type) typedef std::unique_ptr<type> type##Scope;\
								typedef std::shared_ptr<type> type##Ref;
#define IMPL_SMART_POINTER(type) template<typename... Args>\
								 inline static std::unique_ptr<type> CreateScope(Args&&... args)\
								 { return std::make_unique<type>(std::forward<Args>(args)...); }\
								 template<typename... Args>\
								 inline static std::shared_ptr<type> CreateRef(Args&&... args)\
								 { return std::make_shared<type>(std::forward<Args>(args)...); }

#endif // !MACROS_H