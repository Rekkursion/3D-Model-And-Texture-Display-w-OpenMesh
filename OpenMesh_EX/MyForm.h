#pragma once

#include "DotNetUtilities.h"
#include "Mesh/GUA_OM.h"
#include "Mesh/DP.h"

//#define TEST
#define DEBUG

Tri_Mesh *mesh;
Tri_Mesh patch;
xform xf;
xform patchXf;
GLCamera camera;
GLCamera patchCamera;
float fov = 0.7f;
point clickPoint, lastClickPoint;
std::map<int, OMT::VIter> chosenPoint_iterMap;
std::map<int, OMT::FIter> chosenFace_iterMap;
std::map<int, std::pair<glm::vec4, OMT::FIter> > zhongMap;
OMT::VIter chosenPoint_iter;
OMT::FIter chosenFace_iter;
CurrentPicking picking = CurrentPicking::PICK_NONE;
bool shouldDrawPoint = true;
bool shouldDrawWire = true;
bool shouldDrawFace = true;
bool shouldDrawTexture = false;
int prePatchN_faces = 0;
float uvRotateAngle = 0.0f, preUvRotateAngle = 0.0f;
BoundaryStyle boundaryStyle = BoundaryStyle::BOUNDARY_STYLE_SQUARE;
std::string textureFilePath;
WeightCalculatingMethod weightCalcMethod = WeightCalculatingMethod::WEIGHT_CALC_MEAN_VALUE;

void dumpInformation(void);
bool getZhongs();
bool findFacePath(OMT::FIter);
int findShortestPath();
void fillPatchPits();
void rebuildPatch();

glm::mat4 ProjectionMatrix;
glm::mat4 ViewMatrix;
glm::mat4 projection, view;

GLuint patchProgramID;
GLuint patchVaoID, patchVboID;

static const Mouse::button physical_to_logical_map[] = {
	Mouse::NONE, Mouse::ROTATE, Mouse::MOVEXY, Mouse::MOVEZ,
	Mouse::MOVEZ, Mouse::MOVEXY, Mouse::MOVEXY, Mouse::MOVEXY,
};
Mouse::button Mouse_State = Mouse::ROTATE;

namespace OpenMesh_EX {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm ���K�n
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  �b���[�J�غc�禡�{���X
			//
		}

	protected:
		/// <summary>
		/// �M�����ϥΤ����귽�C
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  loadModelToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openModelDialog;
	private: System::Windows::Forms::SaveFileDialog^  saveModelDialog;
	private: System::Windows::Forms::ToolStripMenuItem^  saveModelToolStripMenuItem;
	private: HKOGLPanel::HKOGLPanelControl^  hkoglPanelControl1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::ToolStripMenuItem^  pickToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  pointToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  faceToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  noneToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  clearToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  drawToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  pointsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  wiresToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  facesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  textureToolStripMenuItem;
	private: HKOGLPanel::HKOGLPanelControl^  hkoglPanelControl2;
	private: System::Windows::Forms::Button^  btnDrawPatch;
	private: System::Windows::Forms::ToolStripMenuItem^  boudnaryToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  squareToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  circleToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  weightToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  uniformToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  cotangentToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  meanvalueToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openTextureDialog;
	private: System::Windows::Forms::ToolStripMenuItem^  loadTextureToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  faceFastAddToolStripMenuItem;
	private: System::Windows::Forms::Button^  btnFixPatch;
	private: System::Windows::Forms::TrackBar^  trackBarUvRotateAngle;
	private: System::Windows::Forms::Label^  labelUvRotateAngle;
	protected:

	private:
		/// <summary>
		/// �]�p�u��һݪ��ܼơC
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边�ק�
		/// �o�Ӥ�k�����e�C
		/// </summary>
		void InitializeComponent(void)
		{
			HKOGLPanel::HKCOGLPanelCameraSetting^  hkcoglPanelCameraSetting1 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^  hkcoglPanelPixelFormat1 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			HKOGLPanel::HKCOGLPanelCameraSetting^  hkcoglPanelCameraSetting2 = (gcnew HKOGLPanel::HKCOGLPanelCameraSetting());
			HKOGLPanel::HKCOGLPanelPixelFormat^  hkcoglPanelPixelFormat2 = (gcnew HKOGLPanel::HKCOGLPanelPixelFormat());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadModelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveModelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadTextureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pickToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pointToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->faceToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->faceFastAddToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->noneToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->drawToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pointsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->wiresToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->facesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->textureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->boudnaryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->squareToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->circleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->weightToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->uniformToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->cotangentToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->meanvalueToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openModelDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveModelDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->hkoglPanelControl1 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->hkoglPanelControl2 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->btnDrawPatch = (gcnew System::Windows::Forms::Button());
			this->openTextureDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->btnFixPatch = (gcnew System::Windows::Forms::Button());
			this->trackBarUvRotateAngle = (gcnew System::Windows::Forms::TrackBar());
			this->labelUvRotateAngle = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->fileToolStripMenuItem,
					this->pickToolStripMenuItem, this->drawToolStripMenuItem, this->boudnaryToolStripMenuItem, this->weightToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(8, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(1108, 27);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->loadModelToolStripMenuItem,
					this->saveModelToolStripMenuItem, this->loadTextureToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(45, 23);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// loadModelToolStripMenuItem
			// 
			this->loadModelToolStripMenuItem->Name = L"loadModelToolStripMenuItem";
			this->loadModelToolStripMenuItem->Size = System::Drawing::Size(174, 26);
			this->loadModelToolStripMenuItem->Text = L"Load Model";
			this->loadModelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadModelToolStripMenuItem_Click);
			// 
			// saveModelToolStripMenuItem
			// 
			this->saveModelToolStripMenuItem->Name = L"saveModelToolStripMenuItem";
			this->saveModelToolStripMenuItem->Size = System::Drawing::Size(174, 26);
			this->saveModelToolStripMenuItem->Text = L"Save Model";
			this->saveModelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::saveModelToolStripMenuItem_Click);
			// 
			// loadTextureToolStripMenuItem
			// 
			this->loadTextureToolStripMenuItem->Name = L"loadTextureToolStripMenuItem";
			this->loadTextureToolStripMenuItem->Size = System::Drawing::Size(174, 26);
			this->loadTextureToolStripMenuItem->Text = L"Load Texture";
			this->loadTextureToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadTextureToolStripMenuItem_Click);
			// 
			// pickToolStripMenuItem
			// 
			this->pickToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				this->pointToolStripMenuItem,
					this->faceToolStripMenuItem, this->faceFastAddToolStripMenuItem, this->noneToolStripMenuItem, this->clearToolStripMenuItem
			});
			this->pickToolStripMenuItem->Name = L"pickToolStripMenuItem";
			this->pickToolStripMenuItem->Size = System::Drawing::Size(49, 23);
			this->pickToolStripMenuItem->Text = L"Pick";
			// 
			// pointToolStripMenuItem
			// 
			this->pointToolStripMenuItem->Name = L"pointToolStripMenuItem";
			this->pointToolStripMenuItem->Size = System::Drawing::Size(191, 26);
			this->pointToolStripMenuItem->Text = L"Point";
			this->pointToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::pointToolStripMenuItem_Click);
			// 
			// faceToolStripMenuItem
			// 
			this->faceToolStripMenuItem->Name = L"faceToolStripMenuItem";
			this->faceToolStripMenuItem->Size = System::Drawing::Size(191, 26);
			this->faceToolStripMenuItem->Text = L"Face";
			this->faceToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::faceToolStripMenuItem_Click);
			// 
			// faceFastAddToolStripMenuItem
			// 
			this->faceFastAddToolStripMenuItem->Name = L"faceFastAddToolStripMenuItem";
			this->faceFastAddToolStripMenuItem->Size = System::Drawing::Size(191, 26);
			this->faceFastAddToolStripMenuItem->Text = L"Face (Fast Add)";
			this->faceFastAddToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::faceFastAddToolStripMenuItem_Click);
			// 
			// noneToolStripMenuItem
			// 
			this->noneToolStripMenuItem->Name = L"noneToolStripMenuItem";
			this->noneToolStripMenuItem->Size = System::Drawing::Size(191, 26);
			this->noneToolStripMenuItem->Text = L"None";
			this->noneToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::noneToolStripMenuItem_Click);
			// 
			// clearToolStripMenuItem
			// 
			this->clearToolStripMenuItem->Name = L"clearToolStripMenuItem";
			this->clearToolStripMenuItem->Size = System::Drawing::Size(191, 26);
			this->clearToolStripMenuItem->Text = L"Clear";
			this->clearToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::clearToolStripMenuItem_Click);
			// 
			// drawToolStripMenuItem
			// 
			this->drawToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->pointsToolStripMenuItem,
					this->wiresToolStripMenuItem, this->facesToolStripMenuItem, this->textureToolStripMenuItem
			});
			this->drawToolStripMenuItem->Name = L"drawToolStripMenuItem";
			this->drawToolStripMenuItem->Size = System::Drawing::Size(58, 23);
			this->drawToolStripMenuItem->Text = L"Draw";
			// 
			// pointsToolStripMenuItem
			// 
			this->pointsToolStripMenuItem->Name = L"pointsToolStripMenuItem";
			this->pointsToolStripMenuItem->Size = System::Drawing::Size(135, 26);
			this->pointsToolStripMenuItem->Text = L"Points";
			this->pointsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::pointsToolStripMenuItem_Click);
			// 
			// wiresToolStripMenuItem
			// 
			this->wiresToolStripMenuItem->Name = L"wiresToolStripMenuItem";
			this->wiresToolStripMenuItem->Size = System::Drawing::Size(135, 26);
			this->wiresToolStripMenuItem->Text = L"Wires";
			this->wiresToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::wiresToolStripMenuItem_Click);
			// 
			// facesToolStripMenuItem
			// 
			this->facesToolStripMenuItem->Name = L"facesToolStripMenuItem";
			this->facesToolStripMenuItem->Size = System::Drawing::Size(135, 26);
			this->facesToolStripMenuItem->Text = L"Faces";
			this->facesToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::facesToolStripMenuItem_Click);
			// 
			// textureToolStripMenuItem
			// 
			this->textureToolStripMenuItem->Name = L"textureToolStripMenuItem";
			this->textureToolStripMenuItem->Size = System::Drawing::Size(135, 26);
			this->textureToolStripMenuItem->Text = L"Texture";
			this->textureToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::textureToolStripMenuItem_Click);
			// 
			// boudnaryToolStripMenuItem
			// 
			this->boudnaryToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->squareToolStripMenuItem,
					this->circleToolStripMenuItem
			});
			this->boudnaryToolStripMenuItem->Name = L"boudnaryToolStripMenuItem";
			this->boudnaryToolStripMenuItem->Size = System::Drawing::Size(89, 23);
			this->boudnaryToolStripMenuItem->Text = L"Boundary";
			// 
			// squareToolStripMenuItem
			// 
			this->squareToolStripMenuItem->Name = L"squareToolStripMenuItem";
			this->squareToolStripMenuItem->Size = System::Drawing::Size(134, 26);
			this->squareToolStripMenuItem->Text = L"Square";
			this->squareToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::squareToolStripMenuItem_Click);
			// 
			// circleToolStripMenuItem
			// 
			this->circleToolStripMenuItem->Name = L"circleToolStripMenuItem";
			this->circleToolStripMenuItem->Size = System::Drawing::Size(134, 26);
			this->circleToolStripMenuItem->Text = L"Circle";
			this->circleToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::circleToolStripMenuItem_Click);
			// 
			// weightToolStripMenuItem
			// 
			this->weightToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->uniformToolStripMenuItem,
					this->cotangentToolStripMenuItem, this->meanvalueToolStripMenuItem
			});
			this->weightToolStripMenuItem->Name = L"weightToolStripMenuItem";
			this->weightToolStripMenuItem->Size = System::Drawing::Size(89, 23);
			this->weightToolStripMenuItem->Text = L"Weight";
			// 
			// uniformToolStripMenuItem
			// 
			this->uniformToolStripMenuItem->Name = L"uniformToolStripMenuItem";
			this->uniformToolStripMenuItem->Size = System::Drawing::Size(134, 26);
			this->uniformToolStripMenuItem->Text = L"Uniform";
			this->uniformToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::uniformToolStripMenuItem_Click);
			// 
			// cotangentToolStripMenuItem
			// 
			this->cotangentToolStripMenuItem->Name = L"cotangentToolStripMenuItem";
			this->cotangentToolStripMenuItem->Size = System::Drawing::Size(134, 26);
			this->cotangentToolStripMenuItem->Text = L"Cotangent";
			this->cotangentToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::cotangentToolStripMenuItem_Click);
			// 
			// meanvalueToolStripMenuItem
			// 
			this->meanvalueToolStripMenuItem->Name = L"meanvalueToolStripMenuItem";
			this->meanvalueToolStripMenuItem->Size = System::Drawing::Size(134, 26);
			this->meanvalueToolStripMenuItem->Text = L"Mean Value";
			this->meanvalueToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::meanvalueToolStripMenuItem_Click);
			// 
			// openModelDialog
			// 
			this->openModelDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openModelDialog_FileOk);
			// 
			// saveModelDialog
			// 
			this->saveModelDialog->DefaultExt = L"obj";
			this->saveModelDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::saveModelDialog_FileOk);
			// 
			// hkoglPanelControl1
			// 
			hkcoglPanelCameraSetting1->Far = 1000;
			hkcoglPanelCameraSetting1->Fov = 45;
			hkcoglPanelCameraSetting1->Near = -1000;
			hkcoglPanelCameraSetting1->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl1->Camera_Setting = hkcoglPanelCameraSetting1;
			this->hkoglPanelControl1->Location = System::Drawing::Point(0, 28);
			this->hkoglPanelControl1->Margin = System::Windows::Forms::Padding(4);
			this->hkoglPanelControl1->Name = L"hkoglPanelControl1";
			hkcoglPanelPixelFormat1->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat1->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl1->Pixel_Format = hkcoglPanelPixelFormat1;
			this->hkoglPanelControl1->Size = System::Drawing::Size(550, 550);
			this->hkoglPanelControl1->TabIndex = 2;
			this->hkoglPanelControl1->Load += gcnew System::EventHandler(this, &MyForm::hkoglPanelControl1_Load);
			this->hkoglPanelControl1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::hkoglPanelControl1_Paint);
			this->hkoglPanelControl1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseDown);
			this->hkoglPanelControl1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseMove);
			this->hkoglPanelControl1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl1_MouseWheel);
			// 
			// hkoglPanelControl2
			// 
			hkcoglPanelCameraSetting2->Far = 1000;
			hkcoglPanelCameraSetting2->Fov = 45;
			hkcoglPanelCameraSetting2->Near = -1000;
			hkcoglPanelCameraSetting2->Type = HKOGLPanel::HKCOGLPanelCameraSetting::CAMERATYPE::ORTHOGRAPHIC;
			this->hkoglPanelControl2->Camera_Setting = hkcoglPanelCameraSetting2;
			this->hkoglPanelControl2->Location = System::Drawing::Point(558, 28);
			this->hkoglPanelControl2->Margin = System::Windows::Forms::Padding(4);
			this->hkoglPanelControl2->Name = L"hkoglPanelControl2";
			hkcoglPanelPixelFormat2->Accumu_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat2->Alpha_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			hkcoglPanelPixelFormat2->Stencil_Buffer_Bits = HKOGLPanel::HKCOGLPanelPixelFormat::PIXELBITS::BITS_0;
			this->hkoglPanelControl2->Pixel_Format = hkcoglPanelPixelFormat2;
			this->hkoglPanelControl2->Size = System::Drawing::Size(550, 550);
			this->hkoglPanelControl2->TabIndex = 3;
			this->hkoglPanelControl2->Load += gcnew System::EventHandler(this, &MyForm::hkoglPanelControl2_Load);
			this->hkoglPanelControl2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::hkoglPanelControl2_Paint);
			this->hkoglPanelControl2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl2_MouseDown);
			this->hkoglPanelControl2->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl2_MouseMove);
			this->hkoglPanelControl2->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl2_MouseUp);
			this->hkoglPanelControl2->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::hkoglPanelControl2_MouseWheel);
			// 
			// btnDrawPatch
			// 
			this->btnDrawPatch->Location = System::Drawing::Point(1011, 3);
			this->btnDrawPatch->Name = L"btnDrawPatch";
			this->btnDrawPatch->Size = System::Drawing::Size(93, 23);
			this->btnDrawPatch->TabIndex = 4;
			this->btnDrawPatch->Text = L"Patch";
			this->btnDrawPatch->UseVisualStyleBackColor = true;
			this->btnDrawPatch->Click += gcnew System::EventHandler(this, &MyForm::btnDrawPatch_Click);
			// 
			// openTextureDialog
			// 
			this->openTextureDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openTextureDialog_FileOk);
			// 
			// btnFixPatch
			// 
			this->btnFixPatch->Location = System::Drawing::Point(912, 3);
			this->btnFixPatch->Name = L"btnFixPatch";
			this->btnFixPatch->Size = System::Drawing::Size(93, 23);
			this->btnFixPatch->TabIndex = 5;
			this->btnFixPatch->Text = L"Fix";
			this->btnFixPatch->UseVisualStyleBackColor = true;
			this->btnFixPatch->Click += gcnew System::EventHandler(this, &MyForm::btnFixPatch_Click);
			//
			// trackBarUvRotateAngle
			//
			this->trackBarUvRotateAngle->Location = System::Drawing::Point(626, 3);
			this->trackBarUvRotateAngle->Name = L"trackBarUvRotateAngle";
			this->trackBarUvRotateAngle->Size = System::Drawing::Size(280, 10);
			this->trackBarUvRotateAngle->Value = 0;
			this->trackBarUvRotateAngle->Maximum = 360;
			this->trackBarUvRotateAngle->Minimum = 0;
			this->trackBarUvRotateAngle->ValueChanged += gcnew System::EventHandler(this, &MyForm::trackBarUvRotateAngle_ValueChanged);
			//
			// labelUvRotateAngle
			//
			this->labelUvRotateAngle->Location = System::Drawing::Point(560, 7);
			this->labelUvRotateAngle->Name = L"labelUvRotateAngle";
			//this->trackBarUvRotateAngle->Size = System::Drawing::Size(250, 10);
			this->labelUvRotateAngle->Text = L"UV Angle";
			//
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1108, 586);
			this->Controls->Add(this->btnFixPatch);
			this->Controls->Add(this->btnDrawPatch);
			this->Controls->Add(this->hkoglPanelControl2);
			this->Controls->Add(this->hkoglPanelControl1);
			this->Controls->Add(this->trackBarUvRotateAngle);
			this->Controls->Add(this->labelUvRotateAngle);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"MyForm";
			this->Text = L"OpenMesh";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	// Load panel
	private: System::Void hkoglPanelControl1_Load(System::Object^  sender, System::EventArgs^  e)
	{
		glutInitContextVersion(4, 3);// Base on OpenGL version 4.3
		glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);// Check downward compatibility GLUT_FORWARD_COMPATIBLE
		glutInitContextProfile(GLUT_CORE_PROFILE);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);// Multisample for polygons smooth

		// Call custom initialize function
		glewExperimental = GL_TRUE;// Position before glewInit()
		if (glewInit())
		{
			// C error catch
			std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;
			exit(EXIT_FAILURE);
		}
		else
		{
			// Print debug information
			dumpInformation();
		}
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);

		this->noneToolStripMenuItem->CheckState = CheckState::Checked;

		this->pointsToolStripMenuItem->CheckState = CheckState::Checked;
		this->wiresToolStripMenuItem->CheckState = CheckState::Checked;
		this->facesToolStripMenuItem->CheckState = CheckState::Checked;
		this->textureToolStripMenuItem->CheckState = CheckState::Unchecked;

		this->squareToolStripMenuItem->CheckState = CheckState::Checked;
		this->circleToolStripMenuItem->CheckState = CheckState::Unchecked;

		this->uniformToolStripMenuItem->CheckState = CheckState::Unchecked;
		this->cotangentToolStripMenuItem->CheckState = CheckState::Unchecked;
		this->meanvalueToolStripMenuItem->CheckState = CheckState::Checked;

		lastClickPoint = point();
		patch.LoadTextures("checkerboard4.jpg");
	}

	private: System::Void hkoglPanelControl2_Load(System::Object^  sender, System::EventArgs^  e) {
		patchXf = xform::trans(0.0, 0.0, -1.5) * patchXf;
	}

	// Panel1 paint
	private: System::Void hkoglPanelControl1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		point center;
		center[0] = 0.0;
		center[1] = 0.0;
		center[2] = 0.0;
		camera.setupGL(xf * center, 1.0);

		if (mesh != NULL) {
			projection = camera.getProjectionMatrix();
#ifdef TEST
			std::cout << "projection: " << std::endl;
			for (int r = 0; r < 4; r++) {
				for (int c = 0; c < 4; c++)
					std::cout << projection[r][c] << "\t";
				std::cout << std::endl;
			}
#endif // TEST
			view = xf.getGlmMat4();
#ifdef TEST
			std::cout << "view: " << std::endl;
			for (int r = 0; r < 4; r++) {
				for (int c = 0; c < 4; c++)
					std::cout << view[r][c] << "\t";
				std::cout << std::endl;
			}
#endif // TEST

			chosenPoint_iter = mesh->vertices_begin();
			chosenFace_iter = mesh->faces_begin();

			// new click point
			if (lastClickPoint != clickPoint) {
				lastClickPoint = clickPoint;
				prePatchN_faces = patch.n_faces();

				double mx = clickPoint[0];
				double my = clickPoint[1];
				double mz = clickPoint[2];
				double dis, minDis = 2000000002.0;
				int chosenFace, chosenPoint;
				glm::vec4 point_mvp;
				glm::vec4 mouse_mvp = projection * glm::vec4(mx, my, mz, 1.0);
				bool hasChanged = false;

				#ifdef DEBUG
				//std::cout << "clickPoint|" << clickPoint << "\n";
				//std::cout << "mouse_mvp|" << mouse_mvp[0] << ", " << mouse_mvp[1] << ", " << mouse_mvp[2] << ", " << mouse_mvp[3] << "\n\n";
				#endif

				// Picking point
				if (picking == CurrentPicking::PICK_POINT) {
					chosenPoint = -1;

					// Find the chosen point
					for (OMT::VIter v_it = mesh->vertices_begin(); v_it != mesh->vertices_end(); ++v_it) {
						point_mvp = projection * view * glm::vec4(mesh->point(v_it)[0], mesh->point(v_it)[1], mesh->point(v_it)[2], 1.0);
						dis = ((mouse_mvp[0] - point_mvp[0]) * (mouse_mvp[0] - point_mvp[0])) + ((mouse_mvp[1] - point_mvp[1]) * (mouse_mvp[1] - point_mvp[1])) + ((mouse_mvp[2] - point_mvp[2]) * (mouse_mvp[2] - point_mvp[2]));

						if (dis < minDis) {
							minDis = dis;
							chosenPoint = v_it->idx();
							chosenPoint_iter = v_it;
						}
					}

					if (chosenPoint >= 0) {
						hasChanged = true;
						std::map<int, OMT::VIter>::iterator cp_im_it = chosenPoint_iterMap.find(chosenPoint_iter->idx());

						// The chosen point is NOT in the map, add it
						if (cp_im_it == chosenPoint_iterMap.end()) {
							chosenPoint_iterMap.insert(std::pair<int, OMT::VIter>(chosenPoint_iter->idx(), chosenPoint_iter));

							// Add the 1-ring faces of the chosen point
							for (OMT::VFIter vf_it = mesh->vf_begin(chosenPoint_iter); vf_it != mesh->vf_end(chosenPoint_iter); ++vf_it) {
								std::map<int, OMT::FIter>::iterator find_iter = chosenFace_iterMap.find(vf_it->idx());

								// Not in the map, add it
								if (find_iter == chosenFace_iterMap.end()) {
									for (OMT::FIter f_it = mesh->faces_begin(); f_it != mesh->faces_end(); ++f_it) {
										if (f_it->idx() == vf_it->idx()) {
											chosenFace_iterMap.insert(std::pair<int, OMT::FIter>(vf_it->idx(), f_it));
											break;
										}
									}
								}
							}
						}

						// The chosen point is in the map currently, discard it
						else {
							chosenPoint_iterMap.erase(cp_im_it);

							// Discard the 1-ring faces of the chosen point
							for (OMT::VFIter vf_it = mesh->vf_begin(chosenPoint_iter); vf_it != mesh->vf_end(chosenPoint_iter); ++vf_it) {
								std::map<int, OMT::FIter>::iterator find_iter = chosenFace_iterMap.find(vf_it->idx());

								// In the map, discard it
								if (find_iter != chosenFace_iterMap.end()) {
									chosenFace_iterMap.erase(find_iter);
								}
							}
						}
					}

					/*
					// Create the patch
					patch.clear();

					std::vector<Tri_Mesh::VertexHandle> face_vhs;

					std::deque<Tri_Mesh::VertexHandle> face_vhs_deq;
					std::map<int, Tri_Mesh::VertexHandle> vh_boundaries;
					std::map<int, Tri_Mesh::VertexHandle> vh_chosenPoints;

					// Iterate the map of chosen points
					vh_chosenPoints.clear();
					for (std::map<int, OMT::VIter>::iterator it_map = chosenPoint_iterMap.begin(); it_map != chosenPoint_iterMap.end(); it_map++) {
						// Add chosen point to chosen point map
						vh_chosenPoints.insert(std::pair<int, Tri_Mesh::VertexHandle>(it_map->second->idx(), patch.add_vertex(Tri_Mesh::Point(mesh->point(it_map->second)[0], mesh->point(it_map->second)[1], mesh->point(it_map->second)[2]))));

						#ifdef DEBUG
						//std::cout << "--chosen: " << it_map->second->idx() << "\n";
						#endif
					}

					// Iterate the map of chosen points
					vh_boundaries.clear();
					for (std::map<int, OMT::VIter>::iterator it_map = chosenPoint_iterMap.begin(); it_map != chosenPoint_iterMap.end(); it_map++) {
						// Iterate the 1-ring of the chosen point
						for (OMT::VVIter vv_it = mesh->vv_iter(it_map->second); vv_it; ++vv_it) {

							// Add to 1-ring map if it's NOT added and it's NOT one of chosen points.
							if (vh_boundaries.find(vv_it->idx()) == vh_boundaries.end() && chosenPoint_iterMap.find(vv_it->idx()) == chosenPoint_iterMap.end()) {
								vh_boundaries.insert(std::pair<int, Tri_Mesh::VertexHandle>(vv_it->idx(), patch.add_vertex(Tri_Mesh::Point(mesh->point(vv_it)[0], mesh->point(vv_it)[1], mesh->point(vv_it)[2]))));

								#ifdef DEBUG
								//std::cout << "boundary: " << vv_it->idx() << "\n";
								#endif
							}
						}
					}

					#ifdef DE_BUG
					puts("");

					std::cout << "patch    n vertices: " << patch.n_vertices() << "\n";
					std::cout << "patch       n faces: " << patch.n_faces() << "\n";
					std::cout << "patch       n edges: " << patch.n_edges() << "\n";
					puts("");
					#endif

					// Iterate the map of chosen points
					for (std::map<int, OMT::VIter>::iterator it_map = chosenPoint_iterMap.begin(); it_map != chosenPoint_iterMap.end(); it_map++) {
						face_vhs_deq.clear();

						// Iterate the 1-ring of the chosen point
						for (OMT::VVIter vv_it = mesh->vv_iter(it_map->second); vv_it; ++vv_it) {
							std::map<int, Tri_Mesh::VertexHandle>::iterator vh_it = vh_boundaries.find(vv_it->idx());

							// Add new point to deque
							if (vh_it != vh_boundaries.end()) {
								face_vhs_deq.push_back(vh_it->second);

								// Add new face to patch
								if (face_vhs_deq.size() == 2) {
									face_vhs.clear();
									face_vhs.push_back(face_vhs_deq[1]);
									face_vhs.push_back(face_vhs_deq[0]);
									face_vhs.push_back(vh_chosenPoints[it_map->second->idx()]);

									patch.add_face(face_vhs);

									face_vhs_deq.pop_front();
								}
							}

							else {
								vh_it = vh_chosenPoints.find(vv_it->idx());

								if (vh_it != vh_chosenPoints.end()) {
									face_vhs_deq.push_back(vh_it->second);

									// Add new face to patch
									if (face_vhs_deq.size() == 2) {
										face_vhs.clear();
										face_vhs.push_back(face_vhs_deq[1]);
										face_vhs.push_back(face_vhs_deq[0]);
										face_vhs.push_back(vh_chosenPoints[it_map->second->idx()]);

										patch.add_face(face_vhs);

										face_vhs_deq.pop_front();
									}
								}
							}
						}

						if (face_vhs_deq.size() == 1) {
							std::map<int, Tri_Mesh::VertexHandle>::iterator vh_it = vh_boundaries.find(mesh->vv_iter(it_map->second)->idx());

							if (vh_it != vh_boundaries.end()) {
								face_vhs.clear();
								face_vhs.push_back(vh_it->second);
								face_vhs.push_back(face_vhs_deq[0]);
								face_vhs.push_back(vh_chosenPoints[it_map->second->idx()]);

								patch.add_face(face_vhs);
							}
						}
					}

					if (patch.n_vertices() > 0) {
						patch.init();

						patch.selectedFace.clear();
						patch.selectedFaceSet.clear();
						unsigned int idx = 0;

						for (OMT::FIter f_it = patch.faces_begin(); f_it != patch.faces_end(); ++f_it)
							patch.selectedFaceSet.insert(f_it->idx());
						for (std::set<unsigned int>::iterator it_s = patch.selectedFaceSet.begin(); it_s != patch.selectedFaceSet.end(); ++it_s)
							patch.selectedFace.push_back(*it_s);
						//for (int k = 0; k < patch.n_faces(); k++, idx++)
						//	patch.selectedFace.push_back(idx);
					}
					*/
				}

				// Picking face
				else if (picking == CurrentPicking::PICK_FACE || picking == CurrentPicking::PICK_FACE_FAST_ADD) {
					minDis = 2000000002.0;
					chosenFace = -1;

					// Find the chosen face
					for (std::map<int, std::pair<glm::vec4, OMT::FIter> >::iterator it_m = zhongMap.begin(); it_m != zhongMap.end(); ++it_m) {
						glm::vec4 zhong = projection * view * it_m->second.first;
						dis = ((zhong.x - mouse_mvp.x) * (zhong.x - mouse_mvp.x)) + ((zhong.y - mouse_mvp.y) * (zhong.y - mouse_mvp.y)) + ((zhong.z - mouse_mvp.z) * (zhong.z - mouse_mvp.z));

						if (dis < minDis) {
							minDis = dis;
							chosenFace = it_m->first;
							chosenFace_iter = it_m->second.second;
						}
					}

					if (chosenFace >= 0) {
						hasChanged = true;
						std::map<int, OMT::FIter>::iterator find_iter = chosenFace_iterMap.find(chosenFace_iter->idx());

						// Add chosen face
						if (find_iter == chosenFace_iterMap.end()) {
							if (picking == CurrentPicking::PICK_FACE) {
								chosenFace_iterMap.insert(std::pair<int, OMT::FIter>(chosenFace_iter->idx(), chosenFace_iter));
							}
							else if (picking == CurrentPicking::PICK_FACE_FAST_ADD) {
								if (chosenFace_iterMap.size() == 0)
									chosenFace_iterMap.insert(std::pair<int, OMT::FIter>(chosenFace_iter->idx(), chosenFace_iter));
								else
									findFacePath(chosenFace_iter);
							}
						}

						// Discard chosen face
						else {
							chosenFace_iterMap.erase(find_iter);
						}
					}
				} // End of picking face

				// Patch has been changed, rebuild it
				if (hasChanged) {
					rebuildPatch();
				}

			} // End of new click point

			if (shouldDrawFace) {
				mesh->Render_Solid(projection, view, chosenFace_iter, CurrentPicking::PICK_NONE);
				patch.Render_Solid(projection, view, chosenFace_iter, CurrentPicking::PICK_POINT);
			}

			if (shouldDrawWire)
				mesh->Render_Wireframe(projection, view);

			if (shouldDrawPoint && patch.n_vertices() > 0) {
				patch.Render_Point(projection, view);
				//mesh->Render_Point(projection, view, chosenPoint_iter, picking);
			}

			if (shouldDrawTexture && patch.n_faces() > 0) {
				patch.Render_Texture(projection, view);
			}
		}
	}

	private: System::Void hkoglPanelControl2_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		point center;
		center[0] = 0.0;
		center[1] = 0.0;
		center[2] = 0.0;
		patchCamera.setupGL(patchXf * center, 1.0);

		if (mesh != NULL && patch.n_faces() > 0) {
			mat4 patchProjection = mat4(1.0);
			patchProjection = patchCamera.getProjectionMatrix();

			mat4 patchView = mat4(1.0);
			patchView = patchXf.getGlmMat4();

			patch.Render_PatchPoint(patchProjection, patchView);
			patch.Render_PatchWire(patchProjection, patchView);
		}
	}
	
	// Mouse down function
	private: System::Void hkoglPanelControl1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left ||
			e->Button == System::Windows::Forms::MouseButtons::Middle) {
			point center;
			Mouse_State = Mouse::NONE;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xf * center,
				1.0, xf);

			hkoglPanelControl1->Invalidate();
		}

		if (e->Button == System::Windows::Forms::MouseButtons::Right) {
			point center;
			Mouse_State = Mouse::NONE;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xf * center,
				1.0, xf);

			camera.read_depth(e->X, hkoglPanelControl1->Size.Height - e->Y, clickPoint);
			hkoglPanelControl1->Invalidate();
		}
	}
	
	private: System::Void hkoglPanelControl2_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left ||
			e->Button == System::Windows::Forms::MouseButtons::Middle) {
			point center;
			Mouse_State = Mouse::NONE;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			patchCamera.mouse(e->X, e->Y, Mouse_State,
				patchXf * center,
				1.0, patchXf);

			hkoglPanelControl2->Invalidate();
		}
	}

	// Mouse up function
	private: System::Void hkoglPanelControl1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			hkoglPanelControl1->Invalidate();
		}
		if (e->Button == System::Windows::Forms::MouseButtons::Middle) {
			hkoglPanelControl1->Invalidate();
		}
	}

	private: System::Void hkoglPanelControl2_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			hkoglPanelControl2->Invalidate();
		}
		if (e->Button == System::Windows::Forms::MouseButtons::Middle) {
			hkoglPanelControl2->Invalidate();
		}
	}

	// Mouse move function
	private: System::Void hkoglPanelControl1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		if (e->Button == System::Windows::Forms::MouseButtons::Left)
		{
			point center;
			Mouse_State = Mouse::ROTATE;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xf * center,
				1.0, xf);
			hkoglPanelControl1->Invalidate();
		}
		if (e->Button == System::Windows::Forms::MouseButtons::Middle)
		{
			point center;
			Mouse_State = Mouse::MOVEXY;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xf * center,
				1.0, xf);
			hkoglPanelControl1->Invalidate();
		}
	}

	private: System::Void hkoglPanelControl2_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Middle) {
			point center;
			Mouse_State = Mouse::MOVEXY;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			patchCamera.mouse(e->X, e->Y, Mouse_State,
				patchXf * center,
				1.0, patchXf);
			hkoglPanelControl2->Invalidate();
		}
	}

	// Mouse wheel function
	private: System::Void hkoglPanelControl1_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (e->Delta < 0) {
			point center;
			Mouse_State = Mouse::WHEELDOWN;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xf * center,
				1.0, xf);
			hkoglPanelControl1->Invalidate();
		}
		else {
			point center;
			Mouse_State = Mouse::WHEELUP;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			camera.mouse(e->X, e->Y, Mouse_State,
				xf * center,
				1.0, xf);
			hkoglPanelControl1->Invalidate();
		}
	}

	private: System::Void hkoglPanelControl2_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (e->Delta < 0) {
			point center;
			Mouse_State = Mouse::WHEELDOWN;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			patchCamera.mouse(e->X, e->Y, Mouse_State,
				patchXf * center,
				1.0, patchXf);
			hkoglPanelControl2->Invalidate();
		}

		else {
			point center;
			Mouse_State = Mouse::WHEELUP;
			center[0] = 0.0;
			center[1] = 0.0;
			center[2] = 0.0;
			patchCamera.mouse(e->X, e->Y, Mouse_State,
				patchXf * center,
				1.0, patchXf);
			hkoglPanelControl2->Invalidate();
		}
	}

	// Load menu
	private: System::Void loadModelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		openModelDialog->Filter = "Model(*.obj)|*obj";
		openModelDialog->Multiselect = false;
		openModelDialog->ShowDialog();
	}

	// Get model
	private: System::Void openModelDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
	{
		std::string filename;
		MarshalString(openModelDialog->FileName, filename);

		if (mesh != NULL)
			delete mesh;

		mesh = new Tri_Mesh;

		if (ReadFile(filename, mesh))
		{
			mesh->init();
			std::cout << filename << std::endl;
		}

		patch.clear();
		chosenPoint_iterMap.clear();
		chosenFace_iterMap.clear();

		std::cout << "get zhong: " << getZhongs() << "\n";
		glEnable(GL_DEPTH_TEST);
		//glDepthFunc(GL_LEQUAL);

		glDeleteProgram(patchProgramID);
		patchProgramID = Tri_Mesh::loadShader("patch.vs.glsl", "patch.fs.glsl");

		glDeleteVertexArrays(1, &patchVaoID);
		glGenVertexArrays(1, &patchVaoID);
		glBindVertexArray(patchVaoID);

		hkoglPanelControl1->Invalidate();
	}

	// Load texture
	private: System::Void loadTextureToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		openTextureDialog->Filter = "Texture(*.jpg;*.png)|*.jpg;*.png";
		openTextureDialog->Multiselect = false;
		openTextureDialog->ShowDialog();
	}

	// Get texture
	private: System::Void openTextureDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
		std::string filename;
		MarshalString(openTextureDialog->FileName, filename);

		textureFilePath = filename;
		std::cout << "Texture file path: |" << textureFilePath << "|\n";

		patch.LoadTextures(textureFilePath.c_str());
		patch.Parameterization(uvRotateAngle, boundaryStyle, weightCalcMethod);

		hkoglPanelControl1->Invalidate();
	}

	// Save menu
	private: System::Void saveModelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		saveModelDialog->Filter = "Model(*.obj)|*obj";
		saveModelDialog->ShowDialog();
	}

	// Save model
	private: System::Void saveModelDialog_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
	{
		std::string filename;
		MarshalString(saveModelDialog->FileName, filename);

		if (SaveFile(filename, mesh))
			std::cout << filename << std::endl;
	}

	// Pick point
	private: System::Void pointToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		picking = CurrentPicking::PICK_POINT;

		this->pointToolStripMenuItem->CheckState = CheckState::Checked;
		this->faceToolStripMenuItem->CheckState = CheckState::Unchecked;
		this->faceFastAddToolStripMenuItem->CheckState = CheckState::Unchecked;
		this->noneToolStripMenuItem->CheckState = CheckState::Unchecked;

		hkoglPanelControl1->Invalidate();
	}

	// Pick face
	private: System::Void faceToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		picking = CurrentPicking::PICK_FACE;

		this->pointToolStripMenuItem->CheckState = CheckState::Unchecked;
		this->faceToolStripMenuItem->CheckState = CheckState::Checked;
		this->faceFastAddToolStripMenuItem->CheckState = CheckState::Unchecked;
		this->noneToolStripMenuItem->CheckState = CheckState::Unchecked;

		hkoglPanelControl1->Invalidate();
	}

	// Pick face (Fast add)
	private: System::Void faceFastAddToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		picking = CurrentPicking::PICK_FACE_FAST_ADD;

		this->pointToolStripMenuItem->CheckState = CheckState::Unchecked;
		this->faceToolStripMenuItem->CheckState = CheckState::Unchecked;
		this->faceFastAddToolStripMenuItem->CheckState = CheckState::Checked;
		this->noneToolStripMenuItem->CheckState = CheckState::Unchecked;

		hkoglPanelControl1->Invalidate();
	}
	
	// Pick none
	private: System::Void noneToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		picking = CurrentPicking::PICK_NONE;

		this->pointToolStripMenuItem->CheckState = CheckState::Unchecked;
		this->faceToolStripMenuItem->CheckState = CheckState::Unchecked;
		this->faceFastAddToolStripMenuItem->CheckState = CheckState::Unchecked;
		this->noneToolStripMenuItem->CheckState = CheckState::Checked;
	}

	// Clear patch
	private: System::Void clearToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		patch.clear();
		chosenPoint_iterMap.clear();
		chosenFace_iterMap.clear();

		hkoglPanelControl1->Invalidate();
		hkoglPanelControl2->Invalidate();
	}

	// Should draw points or not
	private: System::Void pointsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		shouldDrawPoint = !shouldDrawPoint;

		if (this->pointsToolStripMenuItem->CheckState == CheckState::Checked)
			this->pointsToolStripMenuItem->CheckState = CheckState::Unchecked;
		else
			this->pointsToolStripMenuItem->CheckState = CheckState::Checked;

		hkoglPanelControl1->Invalidate();
	}

	// Should draw wires or not
	private: System::Void wiresToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		shouldDrawWire = !shouldDrawWire;

		if (this->wiresToolStripMenuItem->CheckState == CheckState::Checked)
			this->wiresToolStripMenuItem->CheckState = CheckState::Unchecked;
		else
			this->wiresToolStripMenuItem->CheckState = CheckState::Checked;

		hkoglPanelControl1->Invalidate();
	}

	// Should draw faces or not
	private: System::Void facesToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		shouldDrawFace = !shouldDrawFace;

		if (this->facesToolStripMenuItem->CheckState == CheckState::Checked)
			this->facesToolStripMenuItem->CheckState = CheckState::Unchecked;
		else
			this->facesToolStripMenuItem->CheckState = CheckState::Checked;

		hkoglPanelControl1->Invalidate();
	}
	
	// Should draw texture or not
	private: System::Void textureToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		shouldDrawTexture = !shouldDrawTexture;

		if (this->textureToolStripMenuItem->CheckState == CheckState::Checked)
			this->textureToolStripMenuItem->CheckState = CheckState::Unchecked;
		else
			this->textureToolStripMenuItem->CheckState = CheckState::Checked;

		hkoglPanelControl1->Invalidate();
	}
	
	private: System::Void btnDrawPatch_Click(System::Object^  sender, System::EventArgs^  e) {
		hkoglPanelControl2->Refresh();
		patch.initPatch();
		hkoglPanelControl2->Invalidate();
	}

	private: System::Void btnFixPatch_Click(System::Object^  sender, System::EventArgs^  e) {
		if (mesh != NULL && patch.n_faces() > 0) {
			fillPatchPits();
			hkoglPanelControl1->Invalidate();
			hkoglPanelControl2->Invalidate();
		}
	}

	private: System::Void trackBarUvRotateAngle_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
		preUvRotateAngle = uvRotateAngle;
		uvRotateAngle = ((double)(trackBarUvRotateAngle->Value) * (double)M_PI) / (double)180.0;

		patch.Parameterization(uvRotateAngle, boundaryStyle, weightCalcMethod);
		hkoglPanelControl2->Refresh();
		patch.initPatch();
		hkoglPanelControl2->Invalidate();
		hkoglPanelControl1->Invalidate();
	}

	// Boundary method - Square
	private: System::Void squareToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		boundaryStyle = BoundaryStyle::BOUNDARY_STYLE_SQUARE;

		this->squareToolStripMenuItem->CheckState = CheckState::Checked;
		this->circleToolStripMenuItem->CheckState = CheckState::Unchecked;

		patch.Parameterization(uvRotateAngle, boundaryStyle, weightCalcMethod);
		hkoglPanelControl2->Refresh();
		patch.initPatch();
		hkoglPanelControl2->Invalidate();
		hkoglPanelControl1->Invalidate();
	}

	// Boundary method - Circle
	private: System::Void circleToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		boundaryStyle = BoundaryStyle::BOUNDARY_STYLE_CIRCLE;

		this->squareToolStripMenuItem->CheckState = CheckState::Unchecked;
		this->circleToolStripMenuItem->CheckState = CheckState::Checked;

		patch.Parameterization(uvRotateAngle, boundaryStyle, weightCalcMethod);
		hkoglPanelControl2->Refresh();
		patch.initPatch();
		hkoglPanelControl2->Invalidate();
		hkoglPanelControl1->Invalidate();
	}

	// Weight Calculating Method - Uniform
	private: System::Void uniformToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		weightCalcMethod = WeightCalculatingMethod::WEIGHT_CALC_UNIFORM;

		this->uniformToolStripMenuItem->CheckState = CheckState::Checked;
		this->cotangentToolStripMenuItem->CheckState = CheckState::Unchecked;
		this->meanvalueToolStripMenuItem->CheckState = CheckState::Unchecked;

		patch.Parameterization(uvRotateAngle, boundaryStyle, weightCalcMethod);
		hkoglPanelControl2->Refresh();
		patch.initPatch();
		hkoglPanelControl2->Invalidate();
		hkoglPanelControl1->Invalidate();
	}

	// Weight Calculating Method - Cotangent
	private: System::Void cotangentToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		weightCalcMethod = WeightCalculatingMethod::WEIGHT_CALC_COTANGENT;

		this->uniformToolStripMenuItem->CheckState = CheckState::Unchecked;
		this->cotangentToolStripMenuItem->CheckState = CheckState::Checked;
		this->meanvalueToolStripMenuItem->CheckState = CheckState::Unchecked;

		patch.Parameterization(uvRotateAngle, boundaryStyle, weightCalcMethod);
		hkoglPanelControl2->Refresh();
		patch.initPatch();
		hkoglPanelControl2->Invalidate();
		hkoglPanelControl1->Invalidate();
	}

	// Weight Calculating Method - Mean-value
	private: System::Void meanvalueToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		weightCalcMethod = WeightCalculatingMethod::WEIGHT_CALC_MEAN_VALUE;

		this->uniformToolStripMenuItem->CheckState = CheckState::Unchecked;
		this->cotangentToolStripMenuItem->CheckState = CheckState::Unchecked;
		this->meanvalueToolStripMenuItem->CheckState = CheckState::Checked;

		patch.Parameterization(uvRotateAngle, boundaryStyle, weightCalcMethod);
		hkoglPanelControl2->Refresh();
		patch.initPatch();
		hkoglPanelControl2->Invalidate();
		hkoglPanelControl1->Invalidate();
	}


};
};

// Information
void dumpInformation()
{
	std::cout << "Vender: " << glGetString(GL_VENDOR) << std::endl
		<< "Renderer: " << glGetString(GL_RENDERER) << std::endl
		<< "Version: " << glGetString(GL_VERSION) << std::endl
		<< "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

// Get zhong xin
bool getZhongs() {
	if (mesh == NULL)
		return false;

	zhongMap.clear();
	for (OMT::FIter f_it = mesh->faces_begin(); f_it != mesh->faces_end(); ++f_it) {
		glm::vec4 zhong = glm::vec4(0.0);
		for (OMT::FVIter fv_it = mesh->fv_begin(f_it); fv_it != mesh->fv_end(f_it); ++fv_it) {
			//zhong += projection * view * glm::vec4(mesh->point(fv_it)[0], mesh->point(fv_it)[1], mesh->point(fv_it)[2], 1.0);
			zhong += glm::vec4(mesh->point(fv_it)[0], mesh->point(fv_it)[1], mesh->point(fv_it)[2], 1.0);
		}
		zhong /= 3.0;

		zhongMap.insert(std::pair<int, std::pair<glm::vec4, OMT::FIter> >(f_it->idx(), std::pair<glm::vec4, OMT::FIter>(zhong, f_it)));
	}

	return true;
}

std::queue<std::pair<int, Tri_Mesh::FaceHandle> > face_que;
std::vector<std::pair<int, Tri_Mesh::FaceHandle> > face_vec;
std::map<int, int> visited;
std::stack<Tri_Mesh::FaceHandle> fh_stk;

bool findFacePath(OMT::FIter chosen_fiter) {
	visited.clear();
	face_vec.clear();

	while (!face_que.empty())
		face_que.pop();

	face_que.push(std::pair<int, Tri_Mesh::FaceHandle>(0, *chosen_fiter));
	face_vec.push_back(std::pair<int, Tri_Mesh::FaceHandle>(0, *chosen_fiter));
	visited.insert(std::pair<int, int>(chosenFace_iter->idx(), 0));

	int successful = findShortestPath();

	return (successful >= 0);
}

int findShortestPath() {
	Tri_Mesh::FaceHandle fh;
	int curStep;

	while (!face_que.empty()) {
		fh = face_que.front().second;
		curStep = face_que.front().first;

		face_que.pop();

		// Reach the goal
		if (chosenFace_iterMap.find(fh.idx()) != chosenFace_iterMap.end()) {

			// Add faces to chosen face iterator map
			for (std::vector<std::pair<int, Tri_Mesh::FaceHandle> >::reverse_iterator r_it_v = face_vec.rbegin(); r_it_v != face_vec.rend(); ++r_it_v) {
				int idx = r_it_v->second.idx();
				for (OMT::FIter f_it = mesh->faces_begin(); f_it != mesh->faces_end(); ++f_it) {
					if (f_it->idx() == idx) {
						chosenFace_iterMap.insert(std::pair<int, OMT::FIter>(idx, f_it));
						break;
					}
				}
			}

			return curStep;
		}

		// Check the rounded faces
		for (OMT::FFIter ff_it = mesh->ff_begin(fh); ff_it != mesh->ff_end(fh); ++ff_it) {

			// Not visited, add to the queue
			if (visited.find(ff_it->idx()) == visited.end()) {
				face_que.push(std::pair<int, Tri_Mesh::FaceHandle>(curStep + 1, *ff_it));
				face_vec.push_back(std::pair<int, Tri_Mesh::FaceHandle>(curStep + 1, *ff_it));

				visited.insert(std::pair<int, int>(ff_it->idx(), curStep + 1));
			}
		}
	}

	return -1;
}

void fillPatchPits() {
	if (mesh == NULL)
		return;

	int adjacentChosenFaceCount;

	for (std::map<int, OMT::FIter>::iterator f_mit = chosenFace_iterMap.begin(); f_mit != chosenFace_iterMap.end(); f_mit++) {
		for (OMT::FFIter ff_it = mesh->ff_begin(*(f_mit->second)); ff_it != mesh->ff_end(*(f_mit->second)); ++ff_it) {
			if (chosenFace_iterMap.find(ff_it->idx()) == chosenFace_iterMap.end()) {
				adjacentChosenFaceCount = 0;

				for (OMT::FFIter ff_it2 = mesh->ff_begin(*ff_it); ff_it2 != mesh->ff_end(*ff_it); ++ff_it2) {
					if (chosenFace_iterMap.find(ff_it2->idx()) != chosenFace_iterMap.end())
						adjacentChosenFaceCount++;
				}

				if (adjacentChosenFaceCount >= 2) {
					for (OMT::FIter f_it = mesh->faces_begin(); f_it != mesh->faces_end(); ++f_it) {
						if (f_it->idx() == ff_it->idx()) {
							chosenFace_iterMap.insert(std::pair<int, OMT::FIter>(f_it->idx(), f_it));
							break;
						}
					}
				}
			}
		}
	}

	rebuildPatch();

	/*
	Tri_Mesh::HalfedgeHandle heh, heh_init;
	int boundaryLength;
	int longestBoundaryIndex, longestBoundaryLength;
	std::set<int> visitedEdges;
	std::map<int, OMT::EIter> boundaryIndices;

	longestBoundaryLength = 0;
	longestBoundaryIndex = -1;

	for (OMT::EIter e_it = patch.edges_begin(); e_it != patch.edges_end(); ++e_it) {
		if (patch.is_boundary(e_it.handle()) && visitedEdges.find(e_it->idx()) == visitedEdges.end()) {

			heh = heh_init = patch.halfedge_handle(e_it.handle(), 1);
			boundaryLength = 0;

			do {
				visitedEdges.insert(heh.idx());
				boundaryLength++;
				heh = patch.next_halfedge_handle(heh);
			} while (heh != heh_init);

			if (boundaryLength > longestBoundaryLength) {
				longestBoundaryIndex = e_it->idx();
				longestBoundaryLength = boundaryLength;
			}

			boundaryIndices.insert(std::pair<int, OMT::EIter>(e_it->idx(), e_it));
		}
	}

	printf("boundaryIndices.size() = %d\n", boundaryIndices.size());

	if (longestBoundaryIndex < 0)
		return;

	for (std::map<int, OMT::EIter>::iterator it_m = boundaryIndices.begin(); it_m != boundaryIndices.end(); it_m++) {
		if (it_m->first == longestBoundaryIndex)
			continue;


	}
	*/

	return;
}

void rebuildPatch() {
	patch.clear();

	std::vector<Tri_Mesh::VertexHandle> face_vhs;
	std::map<int, Tri_Mesh::VertexHandle> vhs;

	for (std::map<int, OMT::FIter>::iterator it_m = chosenFace_iterMap.begin(); it_m != chosenFace_iterMap.end(); ++it_m) {
		face_vhs.clear();

		for (OMT::FVIter fv_it = mesh->fv_begin(it_m->second); fv_it != mesh->fv_end(it_m->second); ++fv_it) {
			Tri_Mesh::VertexHandle vh;
			std::map<int, Tri_Mesh::VertexHandle>::iterator vhs_it = vhs.find(fv_it->idx());

			// not found
			if (vhs_it == vhs.end()) {
				Tri_Mesh::Point p = Tri_Mesh::Point(mesh->point(fv_it)[0], mesh->point(fv_it)[1], mesh->point(fv_it)[2]);
				vh = patch.add_vertex(p);
				vhs.insert(std::pair<int, Tri_Mesh::VertexHandle>(fv_it->idx(), vh));
			}
			// found
			else
				vh = vhs_it->second;

			face_vhs.push_back(vh);
		}

		patch.add_face(face_vhs);
	}

	patch.init();

	patch.selectedFaceSet.clear();
	patch.selectedFace.clear();

	for (OMT::FIter f_it = patch.faces_begin(); f_it != patch.faces_end(); ++f_it)
		patch.selectedFaceSet.insert(f_it->idx());
	for (std::set<unsigned int>::iterator it_s = patch.selectedFaceSet.begin(); it_s != patch.selectedFaceSet.end(); ++it_s)
		patch.selectedFace.push_back(*it_s);

	// Parameterization
	patch.Parameterization(uvRotateAngle, boundaryStyle, weightCalcMethod);

	return;
}