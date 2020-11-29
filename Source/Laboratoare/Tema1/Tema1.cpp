#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);
	
	angle = 0;
	positionBowX = 0;
	positionBowY = 350;
	positionRectangleX = 3;
	positionRectangleY = 350;
	positionTriangleX = 60; 
	positionTriangleY = 342;
	lineHeigth = 40;
	lineWidth = 15;
	stepBowY = 3;
	sceneMinY = 0;
	TWO_PI = 6.28318530718f;
	radiusBow = 60;
	number_balloons = 6;
	number_shurikens = 3;
	triangleAngle = 0;
	rectangleAngle = 0;
	shurikenX = 1;
	shurikenY = 100;
	translateShurikenX = -20;
	translateShurikenY = -40;
	rectangleLength = 60;
	rectangleWidth = 4;
	triangleLength = 10;
	triangleWidth = 20;
	shurikenLength = 30;
	shurikenWidth = 30;
	shurikenWidth2 = 60;
	theta = 0;
	radiusCircle = 40;
	tailHeight = 10;
	tailWidth = 10;
	btnRelease = false;
	arrowSpeed = 0;
	powerBarWidth = 15;
	minPowerBar = 10;
	maxPowerBar = 180;
	powerBarNewPosition = 0;
	power = false;
	releaseArrow = false;
	lives = 3;
	score = 0;
	initialPositionRectangleX = 3;
	initialPositionTriangleX = 60;
	initialBalloonY = -400;
	stepPoweBar = 30;
	shurikenDisplacement = 1500;
	std::cout << "Lives:" << lives << endl;
	std::cout << "Score:" << score << endl;

	for (int i = 0; i < number_balloons; i++) {
		balloons.push_back(balloon());
		balloons[i].x = window->GetResolution().x / 3.f + i * 120 + rand()%200;
		balloons[i].y = initialBalloonY;
		balloons[i].speed = rand() % 50 + 100;
		balloons[i].color = rand() % 2;
		balloons[i].scale = 1.f;
	}

	for (int i = 0; i < number_shurikens; i++) {
		shurikens.push_back(shuriken());
		shurikens[i].x = window->GetResolution().x;
		shurikens[i].y = rand() % window->GetResolution().y;
	}

	// shuriken
	Mesh* shuriken = Object2D::CreateShuriken("shuriken", shurikenLength, shurikenWidth, shurikenWidth2, glm::vec3(0, 0, 1));
	AddMeshToList(shuriken);

	// desenare arc
	Mesh* bow = Object2D::CreateBow("bow", radiusBow, glm::vec3(1, 1, 1));
	AddMeshToList(bow);

	// linia sageata
	Mesh* rectangle = Object2D::CreateRectangle("rectangle", rectangleLength, rectangleWidth, glm::vec3(1, 1, 1), true);
	AddMeshToList(rectangle);

	//capat sageata
	Mesh* triangle = Object2D::CreateTriangle("triangle", triangleLength, triangleWidth, glm::vec3(1, 1, 1));
	AddMeshToList(triangle);

	// balonul rosu
	Mesh* redCircle = Object2D::CreateBalloon("redCircle", radiusCircle, glm::vec3(1, 0, 0)); // rosu
	AddMeshToList(redCircle);

	// balonul galben
	Mesh* yellowCircle = Object2D::CreateBalloon("yellowCircle", radiusCircle, glm::vec3(1, 1, 0)); // galben
	AddMeshToList(yellowCircle);

	// codita
	Mesh* tail = Object2D::CreateTail("tail", tailHeight, tailWidth, glm::vec3(1, 1, 1));
	AddMeshToList(tail);

	// powerbar
	Mesh* powerBar = Object2D::CreateRectangle("powerBar", minPowerBar, powerBarWidth, glm::vec3(1, 0.5f, 0), true);
	AddMeshToList(powerBar);

	glLineWidth(5);
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	angle += 20 * deltaTimeSeconds;
	shurikenX += 0.5f * deltaTimeSeconds;

	// arc
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(0, positionBowY);
	RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);

	if (btnRelease == true) { // cand nu e apasat

		positionRectangleX += arrowSpeed * cos(theta);
		positionTriangleX = positionRectangleX + rectangleLength;

		positionRectangleY += arrowSpeed * sin(theta);
		positionTriangleY = positionRectangleY - triangleWidth / 2;

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(positionRectangleX, positionRectangleY);
		modelMatrix *= Transform2D::Rotate(theta);
		RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(positionTriangleX, positionTriangleY);
		modelMatrix *= Transform2D::Translate(-rectangleLength, (positionRectangleY - positionTriangleY));
		modelMatrix *= Transform2D::Rotate(theta);
		modelMatrix *= Transform2D::Translate(rectangleLength, -(positionRectangleY - positionTriangleY));
		RenderMesh2D(meshes["triangle"], shaders["VertexColor"], modelMatrix);

		if (positionTriangleX > window->GetResolution().x + 250 || positionTriangleY > window->GetResolution().y + 250 || 
			positionTriangleX < 0 || positionTriangleY < 0) {
			positionRectangleX = initialPositionRectangleX;
			positionRectangleY = positionBowY;
			positionTriangleX = initialPositionTriangleX;
			positionTriangleY = positionBowY;
			btnRelease = true;
			releaseArrow = false;
			arrowSpeed = 0;
		}

	} else { // cand e apasat

		arrowSpeed += 0.1f;

		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(positionRectangleX, positionRectangleY);
		modelMatrix *= Transform2D::Rotate(theta);
		RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

		// varf sageata
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(positionTriangleX, positionTriangleY);
		modelMatrix *= Transform2D::Translate(-rectangleLength, (positionRectangleY - positionTriangleY));
		modelMatrix *= Transform2D::Rotate(theta);
		modelMatrix *= Transform2D::Translate(rectangleLength, -(positionRectangleY - positionTriangleY));
		RenderMesh2D(meshes["triangle"], shaders["VertexColor"], modelMatrix);
	}

	// generare baloane
	for (int i = 0; i < number_balloons; i++) {
		if (balloons[i].y >= window->GetResolution().y + 100) {
			balloons[i].y = -200;
			balloons[i].color = rand() % 2;
		}

		if (balloons[i].y < -100) {
			balloons[i].speed = rand() % 50 + 100;
			balloons[i].scale = 1;
		}

		// cercul
		if (balloons[i].color == 0) {
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Scale(1, balloons[i].scale);
			modelMatrix *= Transform2D::Translate(balloons[i].x, balloons[i].y);
			RenderMesh2D(meshes["redCircle"], shaders["VertexColor"], modelMatrix);
		}
		else {
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Scale(1, balloons[i].scale);
			modelMatrix *= Transform2D::Translate(balloons[i].x, balloons[i].y);
			RenderMesh2D(meshes["yellowCircle"], shaders["VertexColor"], modelMatrix);
		}

		// codita
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Scale(1, balloons[i].scale);
		modelMatrix *= Transform2D::Translate(balloons[i].x - lineWidth / 2, balloons[i].y - 2 * lineHeigth);
		RenderMesh2D(meshes["tail"], shaders["VertexColor"], modelMatrix);

		float dx = positionTriangleX - balloons[i].x;
		float dy = positionTriangleY - balloons[i].y;
		float distance = sqrt(dx * dx + dy * dy);

		// coliziunea sageata balon
		if (distance < triangleWidth / 2 + radiusCircle) {

			balloons[i].scale = 0.5f;
			balloons[i].y -= 100;
			balloons[i].speed = -1.5f * balloons[i].speed;

			if (balloons[i].color == 0) {
				score += 1;
			}
			else {
				score -= 1;
			}
			std::cout << "Score:" << score <<endl;
		}
		balloons[i].y += balloons[i].speed * deltaTimeSeconds;
	}

	// generare shurikens
	for (int i = 0; i < number_shurikens; i++) {
		if (shurikens[i].x < -100) {
			shurikens[i].x = window->GetResolution().x;
			shurikens[i].y = rand() % window->GetResolution().y;
		}

		// shuriken
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Translate(shurikens[i].x, shurikens[i].y);
		modelMatrix *= Transform2D::Rotate(angle);
		modelMatrix *= Transform2D::Translate(translateShurikenX, translateShurikenY);
		RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);


		// coliziune sageata shuriken
		float dx = positionTriangleX - shurikens[i].x;
		float dy = positionTriangleY - shurikens[i].y;
		float distance = sqrt(dx * dx + dy * dy);

		if (distance < triangleWidth / 2 + shurikenWidth) {

			shurikens[i].x -= shurikenDisplacement;
			score += 1;
			std::cout << "Score:" << score << endl;
		}

		dx = positionBowX - shurikens[i].x;
		dy = positionBowY - shurikens[i].y;
		distance = sqrt(dx * dx + dy * dy);

		// coliziunea shuriken arc
		if (distance < radiusBow + shurikenWidth) {
			lives = lives - 1;
			std::cout << "Lives: " << lives << endl;
			shurikens[i].x -= shurikenDisplacement;
		}

		if (lives == 0) {
			std::cout << "Game Over!"<< endl;
			exit(1);
		}

		shurikens[i].x -= (shurikenX + i * rand()%5);
	}

	powerBarNewPosition += stepPoweBar * deltaTimeSeconds;

	if (power == true) { // daca am apasat 
		modelMatrix = glm::mat3(1);
		modelMatrix *= Transform2D::Scale(powerBarNewPosition, 1);
		RenderMesh2D(meshes["powerBar"], shaders["VertexColor"], modelMatrix);
	}
	else {
		powerBarNewPosition = 0;
	}
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_W)) {
		positionBowY = glm::min(positionBowY + stepBowY, sceneMaxY - radiusBow);
		if (releaseArrow == false) { // daca sageata nu este aruncata
			positionRectangleY = glm::min(positionRectangleY + stepBowY, sceneMaxY - radiusBow);
			positionTriangleY = glm::min(positionTriangleY + stepBowY, sceneMaxY - radiusBow);
		}
	}

	if (window->KeyHold(GLFW_KEY_S)) {
		positionBowY = glm::max(positionBowY - stepBowY, sceneMinY + radiusBow);
		if (releaseArrow == false) { // daca sageata nu este aruncata
			positionRectangleY = glm::max(positionRectangleY - stepBowY, sceneMinY + radiusBow);
			positionTriangleY = glm::max(positionTriangleY - stepBowY, sceneMinY + radiusBow);
		}
	}
}

void Tema1::OnKeyPress(int key, int mods)
{

}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
	if (releaseArrow == false) { // daca nu a fost lansata sageata
		glViewport(0, 0, window->GetResolution().x, window->GetResolution().y);
		float d1 = mouseX - positionBowX;
		float d2 = window->GetResolution().y - mouseY - positionBowY;
		theta = glm::atan((float)d2, (float)d1);
	}
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	power = true;
	btnRelease = false;
	releaseArrow = false;
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	if (btnRelease == false) { // inca nu e lansata
		btnRelease = true;
	}

	power = false;
	releaseArrow = true;
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
