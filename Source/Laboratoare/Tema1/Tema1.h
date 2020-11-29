#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>

class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

	protected:
		struct balloon {
			float x;
			float y;
			float speed;
			float color;
			float scale;
		};

		struct shuriken {
			float x;
			float y;
		};

		glm::mat3 modelMatrix;
		float angle;
		float positionBowX, positionBowY;
		float sceneMaxY = window->GetResolution().y;
		float positionRectangleX;
		float positionRectangleY;
		float positionTriangleX;
		float positionTriangleY;
		float stepBowY;
		float sceneMinY;
		float TWO_PI;
		float radiusBow;
		int number_balloons;
		int number_shurikens;
		std::vector<balloon> balloons;
		std::vector<shuriken> shurikens;
		float lineHeigth;
		float lineWidth;
		int triangleAngle, rectangleAngle;
		int shurikenX, shurikenY;
		int shurikenLength, shurikenWidth, shurikenWidth2;
		int translateShurikenX, translateShurikenY;
		float theta;
		int rectangleLength, rectangleWidth;
		int triangleLength, triangleWidth;
		float radiusCircle;
		float tailHeight, tailWidth;
		bool btnRelease;
		float arrowSpeed;
		float rectangleNewPositionX;
		float triangleNewPositionX;
		float rectangleNewPositionY;
		float triangleNewPositionY;
		float powerBarWidth;
		float minPowerBar;
		float maxPowerBar;
		float powerBarNewPosition;
		bool power;
		bool releaseArrow;
		int lives;
		float score;
		float initialBalloonY;
		float shurikenDisplacement;
		float initialPositionRectangleX;
		float initialPositionTriangleX;
		float stepPoweBar;
};
