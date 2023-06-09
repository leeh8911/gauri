#pragma once

#include <string>

#include <glm/glm.hpp>

#include "gauri/renderer/shader.h"

// TODO: Must remove!
typedef unsigned int GLenum;

namespace gauri
{
class OpenGLShader : public Shader
{
  public:
    OpenGLShader(const std::string &filepath);
    OpenGLShader(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc);
    ~OpenGLShader() override;

    void Bind() const override;
    void Unbind() const override;

    void SetInt(const std::string &name, int value) override;
    void SetIntArray(const std::string &name, int *values, uint32_t count) override;
    void SetFloat(const std::string &name, float value) override;
    void SetFloat3(const std::string &name, const glm::vec3 &value) override;
    void SetFloat4(const std::string &name, const glm::vec4 &value) override;
    void SetMat4(const std::string &name, const glm::mat4 &value) override;

    const std::string &GetName() const override
    {
        return m_Name;
    }

    void UploadUniformInt(const std::string &name, int value);
    void UploadUniformIntArray(const std::string &name, int *values, uint32_t count);

    void UploadUniformFloat(const std::string &name, float value);
    void UploadUniformFloat2(const std::string &name, const glm::vec2 &values);
    void UploadUniformFloat3(const std::string &name, const glm::vec3 &values);
    void UploadUniformFloat4(const std::string &name, const glm::vec4 &values);
    void UploadUniformMat3(const std::string &name, const glm::mat3 &matrix);
    void UploadUniformMat4(const std::string &name, const glm::mat4 &matrix);

  private:
    std::string ReadFile(const std::string &filepath);
    std::unordered_map<GLenum, std::string> PreProcess(const std::string &source);
    void Compile(const std::unordered_map<GLenum, std::string> &shaderSources);
    uint32_t m_RendererID = 0;
    std::string m_Name{};
};
} // namespace gauri
