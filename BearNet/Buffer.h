#ifndef BEARNET_BUFFER_H
#define BEARNET_BUFFER_H

#include <vector>
#include <assert.h>
#include <sys/types.h>

namespace BearNet {

class Buffer {
public:
    explicit Buffer(size_t initSize) 
        : m_bufVec(initSize) { }
    ~Buffer() { }
public:
    void Write(size_t size);
    void WriteAll() { m_readIndex = m_writeIndex = 0; }
    ssize_t ReadFd(int fd);
    void Append(const char* data, size_t size);
public:
    char* GetWritePtr() { return _Begin() + m_writeIndex; }
    const char* GetWritePtr() const { return _Begin() + m_writeIndex; }
    char* GetReadPtr() { return _Begin() + m_readIndex; }
    const char* GetReadPtr() const { return _Begin() + m_readIndex; }
public:
    size_t GetSize() const { return _BufSize(); }
    size_t GetReadSize() const { return m_writeIndex - m_readIndex; }
    size_t GetWriteSize() const { return _BufSize() - m_writeIndex; }
private:
    char* _Begin() { return m_bufVec.data(); }
    const char* _Begin() const { return m_bufVec.data(); }
    size_t _BufSize() const { return m_bufVec.size(); }
    void _MakeSpace(size_t size);
private:
    std::vector<char> m_bufVec;
    size_t m_readIndex;
    size_t m_writeIndex;
};

}

#endif