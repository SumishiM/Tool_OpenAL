#pragma once
#include "Player.h"
#include <iostream>


SoundPlayer* player;

namespace WinformCPP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::IO;
	using namespace msclr::interop;

	using namespace System::Windows::Forms;
	/// <summary>
	/// Description résumée de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			player = new SoundPlayer();
		}
	protected:
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

	private: System::Windows::Forms::Button^ AddSoundButton;
	private: System::Windows::Forms::Button^ RemoveSoundButton;
	private: System::Windows::Forms::Button^ AddPlaylistButton;
	private: System::Windows::Forms::Button^ SavePlaylistButton;
	private: System::Windows::Forms::ListView^ listView;
	private: System::Windows::Forms::ColumnHeader^ Title;
	private: System::Windows::Forms::ColumnHeader^ Path;


	protected:

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->playButton = (gcnew System::Windows::Forms::Button());
			this->stopButton = (gcnew System::Windows::Forms::Button());
			this->pauseButton = (gcnew System::Windows::Forms::Button());
			this->resumeButton = (gcnew System::Windows::Forms::Button());
			this->volumeTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->volumeValueText = (gcnew System::Windows::Forms::TextBox());

			this->AddSoundButton = (gcnew System::Windows::Forms::Button());
			this->RemoveSoundButton = (gcnew System::Windows::Forms::Button());
			this->AddPlaylistButton = (gcnew System::Windows::Forms::Button());
			this->SavePlaylistButton = (gcnew System::Windows::Forms::Button());

			this->listView = (gcnew System::Windows::Forms::ListView());
			this->Title = (gcnew System::Windows::Forms::ColumnHeader());
			this->Path = (gcnew System::Windows::Forms::ColumnHeader());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->volumeTrackBar))->BeginInit();
			this->SuspendLayout();
			// 
			// playButton
			// 
			this->playButton->Location = System::Drawing::Point(20, 417);
			this->playButton->Name = L"playButton";
			this->playButton->Size = System::Drawing::Size(45, 25);
			this->playButton->TabIndex = 0;
			this->playButton->Text = L"Play";
			this->playButton->UseVisualStyleBackColor = true;
			this->playButton->Click += gcnew System::EventHandler(this, &MyForm::playButton_Click);
			// 
			// stopButton
			// 
			this->stopButton->Location = System::Drawing::Point(70, 417);
			this->stopButton->Name = L"stopButton";
			this->stopButton->Size = System::Drawing::Size(45, 25);
			this->stopButton->TabIndex = 1;
			this->stopButton->Text = L"Stop";
			this->stopButton->UseVisualStyleBackColor = true;
			this->stopButton->Click += gcnew System::EventHandler(this, &MyForm::stopButton_Click);
			// 
			// pauseButton
			// 
			this->pauseButton->Location = System::Drawing::Point(120, 417);
			this->pauseButton->Name = L"pauseButton";
			this->pauseButton->Size = System::Drawing::Size(55, 25);
			this->pauseButton->TabIndex = 2;
			this->pauseButton->Text = L"Pause";
			this->pauseButton->UseVisualStyleBackColor = true;
			this->pauseButton->Click += gcnew System::EventHandler(this, &MyForm::pauseButton_Click);
			// 
			// resumeButton
			// 
			this->resumeButton->Location = System::Drawing::Point(180, 417);
			this->resumeButton->Name = L"resumeButton";
			this->resumeButton->Size = System::Drawing::Size(65, 25);
			this->resumeButton->TabIndex = 3;
			this->resumeButton->Text = L"Resume";
			this->resumeButton->UseVisualStyleBackColor = true;
			this->resumeButton->Click += gcnew System::EventHandler(this, &MyForm::resumeButton_Click);
			// 
			// volumeTrackBar
			// 
			this->volumeTrackBar->Location = System::Drawing::Point(331, 417);
			this->volumeTrackBar->Maximum = 100;
			this->volumeTrackBar->Name = L"volumeTrackBar";
			this->volumeTrackBar->Size = System::Drawing::Size(250, 45);
			this->volumeTrackBar->TabIndex = 4;
			this->volumeTrackBar->TickFrequency = 0;
			this->volumeTrackBar->Scroll += gcnew System::EventHandler(this, &MyForm::volumeTrackBar_Scroll);
			// 
			// volumeValueText
			// 
			this->volumeValueText->Location = System::Drawing::Point(296, 417);
			this->volumeValueText->Name = L"volumeValueText";
			this->volumeValueText->Size = System::Drawing::Size(35, 20);
			this->volumeValueText->TabIndex = 5;
			// 
			// AddSoundButton
			// 
			this->AddSoundButton->Location = System::Drawing::Point(17, 13);
			this->AddSoundButton->Name = L"AddSoundButton";
			this->AddSoundButton->Size = System::Drawing::Size(75, 23);
			this->AddSoundButton->TabIndex = 6;
			this->AddSoundButton->Text = L"Add Sound";
			this->AddSoundButton->UseVisualStyleBackColor = true;
			this->AddSoundButton->Click += gcnew System::EventHandler(this, &MyForm::AddSound_Click);
			// 
			// RemoveSoundButton
			// 
			this->RemoveSoundButton->Location = System::Drawing::Point(99, 12);
			this->RemoveSoundButton->Name = L"RemoveSoundButton";
			this->RemoveSoundButton->Size = System::Drawing::Size(75, 23);
			this->RemoveSoundButton->TabIndex = 7;
			this->RemoveSoundButton->Text = L"Remove Sound";
			this->RemoveSoundButton->UseVisualStyleBackColor = true;
			this->RemoveSoundButton->Click += gcnew System::EventHandler(this, &MyForm::RemoveSound_Click);
			// 
			// AddPlaylistButton
			// 
			this->AddPlaylistButton->Location = System::Drawing::Point(180, 13);
			this->AddPlaylistButton->Name = L"AddPlaylistButton";
			this->AddPlaylistButton->Size = System::Drawing::Size(75, 23);
			this->AddPlaylistButton->TabIndex = 8;
			this->AddPlaylistButton->Text = L"Add Playlist";
			this->AddPlaylistButton->UseVisualStyleBackColor = true;
			this->AddPlaylistButton->Click += gcnew System::EventHandler(this, &MyForm::AddPlaylist_Click);
			// 
			// SavePlaylistButton
			// 
			this->SavePlaylistButton->Location = System::Drawing::Point(262, 12);
			this->SavePlaylistButton->Name = L"SavePlaylistButton";
			this->SavePlaylistButton->Size = System::Drawing::Size(75, 23);
			this->SavePlaylistButton->TabIndex = 9;
			this->SavePlaylistButton->Text = L"Save Playlist";
			this->SavePlaylistButton->UseVisualStyleBackColor = true;
			this->SavePlaylistButton->Click += gcnew System::EventHandler(this, &MyForm::SavePlaylist_Click);
			// 
			// listView1
			// 
			this->listView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) { this->Title, this->Path });
			this->listView->HideSelection = false;
			this->listView->Location = System::Drawing::Point(17, 42);
			this->listView->Name = L"listView1";
			this->listView->Size = System::Drawing::Size(564, 369);
			this->listView->TabIndex = 10;
			this->listView->UseCompatibleStateImageBehavior = false;
			this->listView->View = System::Windows::Forms::View::Details;
			// 
			// Title
			// 
			this->Title->Text = L"Title";
			this->Title->Width = 250;
			// 
			// Path
			// 
			this->Path->Text = L"Path";
			this->Path->Width = 600;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(593, 454);
			this->Controls->Add(this->listView);
			this->Controls->Add(this->SavePlaylistButton);
			this->Controls->Add(this->AddPlaylistButton);
			this->Controls->Add(this->RemoveSoundButton);
			this->Controls->Add(this->AddSoundButton);
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
		player->Stop();

		if (listView->SelectedItems->Count > 0)
		{
			msclr::interop::marshal_context oMarshalContext;
			const char* pParameter = oMarshalContext.marshal_as<const char*>(listView->SelectedItems[0]->SubItems[1]->Text);

			if (player != nullptr) {
				player->Load(pParameter);
			}
		}
		else if (listView->Items->Count > 0) 
		{
			msclr::interop::marshal_context oMarshalContext;
			const char* pParameter = oMarshalContext.marshal_as<const char*>(listView->Items[0]->SubItems[1]->Text);

			if (player != nullptr) {
				player->Load(pParameter);
			}
		}
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

	private: System::Void WinformCPP::MyForm::AddSound_Click(System::Object^ sender, System::EventArgs^ e)
	{
		OpenFileDialog^ openFile = gcnew OpenFileDialog();
		openFile->Filter = "All files (*.*)|*.*|Sound File (*.wav)|*.wav|Sound File (*.ogg)|*.ogg";
		openFile->Title = "Select Sound File";
		openFile->FilterIndex = 1;

		if (openFile->ShowDialog() == Windows::Forms::DialogResult::OK)
		{
			String^ selectedFilePath = openFile->FileName;
			String^ fileName = Path::GetFileNameWithoutExtension(selectedFilePath);

			array<String^>^ item1 = { fileName, selectedFilePath };

			ListViewItem^ listViewItem1 = gcnew ListViewItem(item1);

			listView->Items->Add(listViewItem1);
		}
	}

	private: System::Void WinformCPP::MyForm::RemoveSound_Click(System::Object^ sender, System::EventArgs^ e)
	{
		for (int j = listView->SelectedItems->Count - 1; j >= 0; --j)
		{
			for (int i = listView->Items->Count - 1; i >= 0; --i)
			{
				if (listView->SelectedItems[j]->SubItems[0]->Text ==
					listView->Items[i]->SubItems[0]->Text)
				{
					listView->Items->RemoveAt(i);
					i = -1;
				}
			}
		}
	}

	private: System::Void WinformCPP::MyForm::AddPlaylist_Click(System::Object^ sender, System::EventArgs^ e)
	{
		OpenFileDialog^ ofd = gcnew OpenFileDialog();

		ofd->Title = "Open Playlist";
		ofd->Filter = "Playlist (*.json)|*.json";

		if (ofd->ShowDialog() == Windows::Forms::DialogResult::OK)
		{
			String^ pathFile = ofd->FileName;

			std::string pathFileStd = msclr::interop::marshal_as<std::string>(pathFile);

			StreamReader^ lecteurFichier = gcnew StreamReader(pathFile);

			String^ contenuJSON = lecteurFichier->ReadToEnd();

			lecteurFichier->Close();

			String^ writer = gcnew String("");
			bool write = false;
			array<String^>^ item = gcnew array<String^>(2);

			listView->Items->Clear();

			int count = 0;
			for (int i = 0; i < contenuJSON->Length; i++)
			{
				if (write)
				{
					if (contenuJSON[i] == '}')
					{
						write = false;

						if (count < 2)
						{
							item[count] = writer;

							++count;
						}
						if (count >= 2)
						{
							count = 0;

							ListViewItem^ listViewItem1 = gcnew ListViewItem(item);

							listView->Items->Add(listViewItem1);
						}
					}
					else
					{
						writer += contenuJSON[i];
					}
				}
				else
				{
					if (contenuJSON[i] == '{')
					{
						writer = "";
						write = true;
					}
				}
			}
		}
	}

	private: System::Void WinformCPP::MyForm::SavePlaylist_Click(System::Object^ sender, System::EventArgs^ e)
	{
		SaveFileDialog^ SaveFile = gcnew SaveFileDialog();

		SaveFile->Filter = "Playlist (*.json)|*.json";
		SaveFile->Title = "Save Playlist";

		if (SaveFile->ShowDialog() == Windows::Forms::DialogResult::OK)
		{
			String^ pathFile = SaveFile->FileName;
			StreamWriter^ fichierJSON = gcnew StreamWriter(pathFile);

			if (fichierJSON->BaseStream != nullptr)
			{
				String^ jsonFile = "[\n";

				for (int i = 0; i < listView->Items->Count; i++)
				{
					String^ path = listView->Items[i]->SubItems[1]->Text;

					String^ CurrentElement = "";
					CurrentElement += "[\n";
					CurrentElement += "\"Name\": ";
					CurrentElement += "\"{" + listView->Items[i]->SubItems[0]->Text + "}\",\n";
					CurrentElement += "\"Path\": ";
					CurrentElement += "\"{" + path + "}\"\n";
					CurrentElement += "]";

					if (i < listView->Items->Count - 1)
					{
						CurrentElement += ",";
					}

					CurrentElement += "\n";
					jsonFile += CurrentElement;
				}

				jsonFile += "]";

				fichierJSON->Write(jsonFile);
				fichierJSON->Close();

			}
			else
			{
				Console::WriteLine("Open file error JSON.");
			}
		}
	}


	};
}
