//
// AchievementsPage.xaml.cpp
// Implementation of the AchievementsPage class
//

#include "pch.h"
#include "AchievementsPage.xaml.h"
#include "MenuPage.xaml.h"


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
using namespace Windows::UI::Xaml::Media::Imaging; 
// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

AchievementsPage::AchievementsPage()
{
	InitializeComponent();
	CheckAchievements();
}

/// <summary>
/// Invoked when this page is about to be displayed in a Frame.
/// </summary>
/// <param name="e">Event data that describes how this page was reached.  The Parameter
/// property is typically used to configure the page.</param>
void AchievementsPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	(void) e;	// Unused parameter
}

void Project::AchievementsPage::backButton_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(MenuPage::typeid,this);
}

void Project::AchievementsPage::CheckAchievements()
{
	auto uri = ref new Uri("ms-appx:///Assets/tick.png");
	auto urp = ref new Uri("ms-appx:///Assets/pending.png");
	bool isComplete(false),isAllGold(false),isOnSpree(false),isOnUSpree(false),isTimeSavvy(false),isTimeUSavvy(false),isUSubmitter(false);
	ApplicationDataContainer^ localSettings = ApplicationData::Current->LocalSettings;
	auto composit = safe_cast<ApplicationDataCompositeValue^>(localSettings->Values->Lookup("Achievements"));
	if (composit!=nullptr)
	{
		isComplete = safe_cast<IPropertyValue^>(composit->Lookup("isComplete"))->GetBoolean();
		isAllGold = safe_cast<IPropertyValue^>(composit->Lookup("isAllGold"))->GetBoolean();
		isOnSpree = safe_cast<IPropertyValue^>(composit->Lookup("isOnSpree"))->GetBoolean();
		isOnUSpree = safe_cast<IPropertyValue^>(composit->Lookup("isOnUSpree"))->GetBoolean();
		isTimeSavvy = safe_cast<IPropertyValue^>(composit->Lookup("isTimeSavvy"))->GetBoolean();
		isTimeUSavvy = safe_cast<IPropertyValue^>(composit->Lookup("isTimeUSavvy"))->GetBoolean();
		isUSubmitter = safe_cast<IPropertyValue^>(composit->Lookup("isUSubmitter"))->GetBoolean();
	}
	auto urs = (isComplete)?uri:urp;	
	isCompleteText->Source= ref new BitmapImage(urs);
	urs = (isAllGold)?uri:urp;	
	IsAllGoldImg->Source= ref new BitmapImage(urs);
	urs = (isOnSpree)?uri:urp;	
	isOnSpreeImg->Source= ref new BitmapImage(urs);
	urs = (isOnUSpree)?uri:urp;	
	isOnUSpreeImg->Source= ref new BitmapImage(urs);
	urs = (isTimeSavvy)?uri:urp;	
	isTimeSavvyImg->Source= ref new BitmapImage(urs);
	urs = (isTimeUSavvy)?uri:urp;	
	IsTimeUSavvyImg->Source= ref new BitmapImage(urs);
	urs = (isUSubmitter)?uri:urp;	
	IsUSubmitterImg->Source= ref new BitmapImage(urs);
}
		
