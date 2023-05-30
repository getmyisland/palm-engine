#include <glad/glad.h> // holds all OpenGL type declarations

#include "Renderer.h"

namespace PalmEngine
{
	Renderer::Renderer(const Model& model, const Shader& shader) : _model(model), _shader(shader)
	{

	}

	Renderer::~Renderer()
	{

	}

	void Renderer::Render(const Transform& transform)
	{
		for (auto& mesh : _model.GetMeshes())
		{
			_shader.Use();

			// View/Projection Transformations
			glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float)800 / (float)600, 0.1f, 100.0f);
			glm::mat4 view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
			_shader.SetMat4("projection", projection);
			_shader.SetMat4("view", view);

			// Render the mesh
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, transform.GetLocalPosition());
			model = glm::scale(model, transform.GetLocalScale());
			_shader.SetMat4("model", model);

			glActiveTexture(GL_TEXTURE0 + 0);
			// Set the sampler to the correct texture unit
			glUniform1i(glGetUniformLocation(_shader.mID, "texture_albedo"), 0);
			// Bind the texture
			glBindTexture(GL_TEXTURE_2D, mesh.GetAlbedoTexture().mID);

			glActiveTexture(GL_TEXTURE0 + 1);
			// Set the sampler to the correct texture unit
			glUniform1i(glGetUniformLocation(_shader.mID, "texture_normal"), 1);
			// Bind the texture
			glBindTexture(GL_TEXTURE_2D, mesh.GetNormalTexture().mID);

			// Draw mesh
			glBindVertexArray(mesh.GetVAO());
			glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(mesh.GetIndices().size()), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			// Set everything back to default
			glActiveTexture(GL_TEXTURE0);
		}
	}
}