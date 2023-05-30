/*!
 * @file buffer.h
 * @author Sangwon Lee
 * @brief
 * @version 0.1
 * @date 2023-05-30
 *
 * @copyright Copyright (c) 2023
 */

#pragma once

namespace gauri
{
class VertexBuffer
{
  public:
    virtual ~VertexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    static VertexBuffer *Create(float *vertices, uint32_t size);
};

class IndexBuffer
{
  public:
    virtual ~IndexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual uint32_t GetCount() const = 0;

    static IndexBuffer *Create(uint32_t *indices, uint32_t count);
};
} // namespace gauri
