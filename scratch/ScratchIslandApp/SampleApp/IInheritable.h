// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once

// Use this macro to quickly implement both getters and the setter for an
// inheritable setting property. This is similar to the WINRT_PROPERTY macro, except...
// - Has(): checks if the user explicitly set a value for this setting
// - SourceGetter(): return the object that provides the resolved value
// - Getter(): return the resolved value
// - Setter(): set the value directly
// - Clear(): clear the user set value
// - the setting is saved as an optional, where nullopt means
//   that we must inherit the value from our parent
#define INHERITABLE_SETTING(projectedType, type, name, ...)                 \
public:                                                                     \
    /* Returns true if the user explicitly set the value, false otherwise*/ \
    bool Has##name() const                                                  \
    {                                                                       \
        return _##name.has_value();                                         \
    }                                                                       \
                                                                            \
    projectedType name##OverrideSource()                                    \
    {                                                                       \
        /*user set value was not set*/                                      \
        /*iterate through parents to find one with a value*/                \
        for (auto& parent : _parents)                                       \
        {                                                                   \
            if (auto source{ parent->_get##name##OverrideSourceImpl() })    \
            {                                                               \
                return source;                                              \
            }                                                               \
        }                                                                   \
                                                                            \
        /*no value was found*/                                              \
        return nullptr;                                                     \
    }                                                                       \
                                                                            \
    /* Returns the resolved value for this setting */                       \
    /* fallback: user set value --> inherited value --> system set value */ \
    type name() const                                                       \
    {                                                                       \
        const auto val{ _get##name##Impl() };                               \
        return val ? *val : type{ __VA_ARGS__ };                            \
    }                                                                       \
                                                                            \
    /* Overwrite the user set value */                                      \
    void name(const type& value)                                            \
    {                                                                       \
        _##name = value;                                                    \
    }                                                                       \
                                                                            \
    /* Clear the user set value */                                          \
    void Clear##name()                                                      \
    {                                                                       \
        _##name = std::nullopt;                                             \
    }                                                                       \
                                                                            \
private:                                                                    \
    std::optional<type> _##name{ std::nullopt };                            \
    std::optional<type> _get##name##Impl() const                            \
    {                                                                       \
        /*return user set value*/                                           \
        if (_##name)                                                        \
        {                                                                   \
            return _##name;                                                 \
        }                                                                   \
                                                                            \
        /*user set value was not set*/                                      \
        /*iterate through parents to find a value*/                         \
        for (const auto& parent : _parents)                                 \
        {                                                                   \
            if (auto val{ parent->_get##name##Impl() })                     \
            {                                                               \
                return val;                                                 \
            }                                                               \
        }                                                                   \
                                                                            \
        /*no value was found*/                                              \
        return std::nullopt;                                                \
    }                                                                       \
    projectedType _get##name##OverrideSourceImpl() const                    \
    {                                                                       \
        /*we have a value*/                                                 \
        if (_##name)                                                        \
        {                                                                   \
            return *this;                                                   \
        }                                                                   \
                                                                            \
        /*user set value was not set*/                                      \
        /*iterate through parents to find one with a value*/                \
        for (const auto& parent : _parents)                                 \
        {                                                                   \
            if (auto source{ parent->_get##name##OverrideSourceImpl() })    \
            {                                                               \
                return source;                                              \
            }                                                               \
        }                                                                   \
                                                                            \
        /*no value was found*/                                              \
        return nullptr;                                                     \
    }

// This macro is similar to the one above, but is reserved for optional settings
// like Profile.Foreground (where null is interpreted
// as an acceptable value, rather than "inherit")
// "type" is exposed as an IReference
#define INHERITABLE_NULLABLE_SETTING(projectedType, type, name, ...)        \
public:                                                                     \
    /* Returns true if the user explicitly set the value, false otherwise*/ \
    bool Has##name() const                                                  \
    {                                                                       \
        return _##name.has_value();                                         \
    }                                                                       \
                                                                            \
    projectedType name##OverrideSource()                                    \
    {                                                                       \
        /*user set value was not set*/                                      \
        /*iterate through parents to find one with a value*/                \
        for (const auto& parent : _parents)                                 \
        {                                                                   \
            if (auto source{ parent->_get##name##OverrideSourceImpl() })    \
            {                                                               \
                return source;                                              \
            }                                                               \
        }                                                                   \
                                                                            \
        /*no source was found*/                                             \
        return nullptr;                                                     \
    }                                                                       \
                                                                            \
    /* Returns the resolved value for this setting */                       \
    /* fallback: user set value --> inherited value --> system set value */ \
    winrt::Windows::Foundation::IReference<type> name() const               \
    {                                                                       \
        const auto val{ _get##name##Impl() };                               \
        if (val)                                                            \
        {                                                                   \
            if (*val)                                                       \
            {                                                               \
                return **val;                                               \
            }                                                               \
            return nullptr;                                                 \
        }                                                                   \
        return winrt::Windows::Foundation::IReference<type>{ __VA_ARGS__ }; \
    }                                                                       \
                                                                            \
    /* Overwrite the user set value */                                      \
    void name(const winrt::Windows::Foundation::IReference<type>& value)    \
    {                                                                       \
        if (value) /*set value is different*/                               \
        {                                                                   \
            _##name = std::optional<type>{ value.Value() };                 \
        }                                                                   \
        else                                                                \
        {                                                                   \
            /* note we're setting the _inner_ value */                      \
            _##name = std::optional<type>{ std::nullopt };                  \
        }                                                                   \
    }                                                                       \
                                                                            \
    /* Clear the user set value */                                          \
    void Clear##name()                                                      \
    {                                                                       \
        _##name = std::nullopt;                                             \
    }                                                                       \
                                                                            \
private:                                                                    \
    NullableSetting<type> _##name{};                                        \
    NullableSetting<type> _get##name##Impl() const                          \
    {                                                                       \
        /*return user set value*/                                           \
        if (_##name)                                                        \
        {                                                                   \
            return _##name;                                                 \
        }                                                                   \
                                                                            \
        /*user set value was not set*/                                      \
        /*iterate through parents to find a value*/                         \
        for (const auto& parent : _parents)                                 \
        {                                                                   \
            if (auto val{ parent->_get##name##Impl() })                     \
            {                                                               \
                return val;                                                 \
            }                                                               \
        }                                                                   \
                                                                            \
        /*no value was found*/                                              \
        return std::nullopt;                                                \
    }                                                                       \
    projectedType _get##name##OverrideSourceImpl() const                    \
    {                                                                       \
        /*we have a value*/                                                 \
        if (_##name)                                                        \
        {                                                                   \
            return *this;                                                   \
        }                                                                   \
                                                                            \
        /*user set value was not set*/                                      \
        /*iterate through parents to find one with a value*/                \
        for (const auto& parent : _parents)                                 \
        {                                                                   \
            if (auto source{ parent->_get##name##OverrideSourceImpl() })    \
            {                                                               \
                return source;                                              \
            }                                                               \
        }                                                                   \
                                                                            \
        /*no value was found*/                                              \
        return nullptr;                                                     \
    }
