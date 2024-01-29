#pragma once
#include "Player.h"

SoundPlayer* player;

namespace WinformCPP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Description résumée de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: ajoutez ici le code du constructeur
			//
			//player = new SoundPlayer();
		}
	protected:
		/// <summary>
		/// Nettoyage des ressources utilisées.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ playButton;
	protected:
	private: System::Windows::Forms::Button^ stopButton;
	private: System::Windows::Forms::Button^ pauseButton;
	private: System::Windows::Forms::Button^ resumeButton;
	private: System::Windows::Forms::TrackBar^ volumeTrackBar;
	private: System::Windows::Forms::TextBox^ volumeValueText;

	protected:

	private:
		/// <summary>
		/// Variable nécessaire au concepteur.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
		/// le contenu de cette méthode avec l'éditeur de code.
		/// </summary>
		void InitializeComponent(void)
		{
			this->playButton = (gcnew System::Windows::Forms::Button());
			this->stopButton = (gcnew System::Windows::Forms::Button());
			this->pauseButton = (gcnew System::Windows::Forms::Button());
			this->resumeButton = (gcnew System::Windows::Forms::Button());
			this->volumeTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->volumeValueText = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->volumeTrackBar))->BeginInit();
			this->SuspendLayout();
			// 
			// playButton
			// 
			this->playButton->Location = System::Drawing::Point(10, 525);
			this->playButton->Name = L"playButton";
			this->playButton->Size = System::Drawing::Size(45, 25);
			this->playButton->TabIndex = 0;
			this->playButton->Text = L"Play";
			this->playButton->UseVisualStyleBackColor = true;
			this->playButton->Click += gcnew System::EventHandler(this, &MyForm::playButton_Click);
			// 
			// stopButton
			// 
			this->stopButton->Location = System::Drawing::Point(60, 525);
			this->stopButton->Name = L"stopButton";
			this->stopButton->Size = System::Drawing::Size(45, 25);
			this->stopButton->TabIndex = 1;
			this->stopButton->Text = L"Stop";
			this->stopButton->UseVisualStyleBackColor = true;
			this->stopButton->Click += gcnew System::EventHandler(this, &MyForm::stopButton_Click);
			// 
			// pauseButton
			// 
			this->pauseButton->Location = System::Drawing::Point(110, 525);
			this->pauseButton->Name = L"pauseButton";
			this->pauseButton->Size = System::Drawing::Size(55, 25);
			this->pauseButton->TabIndex = 2;
			this->pauseButton->Text = L"Pause";
			this->pauseButton->UseVisualStyleBackColor = true;
			this->pauseButton->Click += gcnew System::EventHandler(this, &MyForm::pauseButton_Click);
			// 
			// resumeButton
			// 
			this->resumeButton->Location = System::Drawing::Point(170, 525);
			this->resumeButton->Name = L"resumeButton";
			this->resumeButton->Size = System::Drawing::Size(65, 25);
			this->resumeButton->TabIndex = 3;
			this->resumeButton->Text = L"Resume";
			this->resumeButton->UseVisualStyleBackColor = true;
			this->resumeButton->Click += gcnew System::EventHandler(this, &MyForm::resumeButton_Click);
			// 
			// volumeTrackBar
			// 
			this->volumeTrackBar->Location = System::Drawing::Point(850, 525);
			this->volumeTrackBar->Maximum = 100;
			this->volumeTrackBar->Name = L"volumeTrackBar";
			this->volumeTrackBar->Size = System::Drawing::Size(250, 45);
			this->volumeTrackBar->TabIndex = 4;
			this->volumeTrackBar->TickFrequency = 0;
			this->volumeTrackBar->Scroll += gcnew System::EventHandler(this, &MyForm::volumeTrackBar_Scroll);
			// 
			// volumeValueText
			// 
			this->volumeValueText->Location = System::Drawing::Point(815, 525);
			this->volumeValueText->Name = L"volumeValueText";
			this->volumeValueText->Size = System::Drawing::Size(35, 20);
			this->volumeValueText->TabIndex = 5;
			//this->volumeValueText->TextAlign = HorizontalAlignment::Right;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(756, 495);
			this->Controls->Add(this->volumeValueText);
			this->Controls->Add(this->volumeTrackBar);
			this->Controls->Add(this->resumeButton);
			this->Controls->Add(this->pauseButton);
			this->Controls->Add(this->stopButton);
			this->Controls->Add(this->playButton);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->volumeTrackBar))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void WinformCPP::MyForm::playButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (player != nullptr)
		player->LoadWav("Ruisseau_Escattes_01.wav");
	}

	private: System::Void WinformCPP::MyForm::stopButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (player != nullptr)
			player->Stop();
	}

	private: System::Void WinformCPP::MyForm::pauseButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (player != nullptr)
			player->Pause();
	}

	private: System::Void WinformCPP::MyForm::resumeButton_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (player != nullptr)
			player->Resume();
	}

	private: System::Void WinformCPP::MyForm::volumeTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e)
	{
		volumeValueText->Text = "" + volumeTrackBar->Value + "%";
		if (player != nullptr)
			player->SetVolume(volumeTrackBar->Value / 100.f);
	}
	};
}
