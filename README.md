Strong Types for C++
====================

This is a simple header-only library for strong types. It follows an idea by 
[Jonathan Boccara](https://www.fluentcpp.com),
as presented in [this](https://www.fluentcpp.com/2016/12/08/strong-types-for-strong-interfaces/) blog post.

## Install

All you have to do is include the single header file `include/strong_types.h`.

## Usage

The main idea is to wrap basic type like an `int` in a templated class together with
an extra template parameter that helps telling one type from another. Therefore, the basic 
usage is:

```
Type<int, struct MyNamedParam> myVar{3};
```

To avoid boilerplate code, the library comes with a single macro:

```
STRONG_TYPE(MyType, int);
```

This declares a new strong type `MyType` with basic type `int`.

If you want to avoid macros, you can also write:
```
using MyType = Type<int, struct ParamMyType>;
```

That's exactly what the macro does.
