#pragma once

struct noncopyable
{
    noncopyable() = default;
    noncopyable(const noncopyable&) = delete;
    noncopyable& operator=(const noncopyable&) = delete;
    // TODO: Figure out the exact reason why this has to be here:
    // NOTE: This must also be used in the derived class.
    noncopyable(noncopyable&&) = default;
    noncopyable& operator=(noncopyable&&) = default;
    // !TODO
};
