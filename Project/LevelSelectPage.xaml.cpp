//
// LevelSelectPage.xaml.cpp
// Implementation of the LevelSelectPage class
//

#include "pch.h"
#include "LevelSelectPage.xaml.h"
#include <MainPage.xaml.h>

using namespace Project;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Storage;

// The Basic Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234237

LevelSelectPage::LevelSelectPage()
{
	InitializeComponent();
}

/// <summary>
/// Populates the page with content passed during navigation.  Any saved state is also
/// provided when recreating a page from a prior session.
/// </summary>
/// <param name="navigationParameter">The parameter value passed to
/// <see cref="Frame::Navigate(Type, Object)"/> when this page was initially requested.
/// </param>
/// <param name="pageState">A map of state preserved by this page during an earlier
/// session.  This will be null the first time a page is visited.</param>
void LevelSelectPage::LoadState(Object^ navigationParameter, IMap<String^, Object^>^ pageState)
{
	(void) navigationParameter;	// Unused parameter
	(void) pageState;	// Unused parameter
}

/// <summary>
/// Preserves state associated with this page in case the application is suspended or the
/// page is discarded from the navigation cache.  Values must conform to the serialization
/// requirements of <see cref="SuspensionManager::SessionState"/>.
/// </summary>
/// <param name="pageState">An empty map to be populated with serializable state.</param>
void LevelSelectPage::SaveState(IMap<String^, Object^>^ pageState)
{
	(void) pageState;	// Unused parameter
}


void Project::LevelSelectPage::PageLoadedHandler(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	levelsvector = ref new Platform::Collections::Vector<Levels^>();
	auto localSettings = ApplicationData::Current->LocalSettings;
	auto HighestLevelReach = safe_cast<String^>(localSettings->Values->Lookup("HighestLevelReached"));
	for(int i=0;i<32;i++)
		AddLevel(ConvertToPString(i+1),"1:00","Gold");
	itemListView->ItemsSource= levels;
}

Platform::String^ LevelSelectPage::ConvertToPString(int val)
	{
		char char_str[10];
		_itoa_s(val,char_str,10);
		std::string s_str = std::string(char_str);
		std::wstring wid_str = std::wstring(s_str.begin(), s_str.end());
		const wchar_t* w_char = wid_str.c_str();
		Platform::String^ p_string = ref new Platform::String(w_char);
		return p_string;
	}
int LevelSelectPage::ConvertToInt(Platform::String^ initial)
{
	const wchar_t *W = initial->Data();
	int Size = wcslen( W );
	char *CString= new char[Size + 1];
	CString[ Size ] = 0;
	for(int y=0;y<Size; y++)
	{
		CString[y] = (char)W[y];
	}
		return atoi(CString);
}


void Project::LevelSelectPage::ItemListView_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{
	if (SettingsAnimatedPopup->IsOpen) { SettingsAnimatedPopup->IsOpen = false; }
	auto lev = safe_cast<Levels^>(itemListView->SelectedItem);
	if (!SettingsAnimatedPopup->IsOpen) 
            {
                RootPopupBorder->Width = 646;
				SettingsAnimatedPopup->HorizontalOffset = Window::Current->Bounds.Width-646;
				LevelNumber->Text=lev->number;
				BestMedalText->Text=lev->BestMedal;
				BestTimeText->Text=lev->BestTime;
                SettingsAnimatedPopup->IsOpen = true; 
            }
}


void Project::LevelSelectPage::CloseSettingsPopupClicked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (SettingsAnimatedPopup->IsOpen) { SettingsAnimatedPopup->IsOpen = false; }
}


void Project::LevelSelectPage::StartSettingsPopupClicked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
		auto lev = safe_cast<Levels^>(itemListView->SelectedItem);
		this->Frame->Navigate(MainPage::typeid,lev->number);
}
