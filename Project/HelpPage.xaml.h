//
// HelpPage.xaml.h
// Declaration of the HelpPage class
//

#pragma once

#include "HelpPage.g.h"

namespace Project
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class HelpPage sealed
	{
	public:
		HelpPage();

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
	private:
		void backButton_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
