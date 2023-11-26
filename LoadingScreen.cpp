#include "LoadingScreen.h"
#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MoviePlayer.h"

#define LOCTEXT_NAMESPACE "LoadingScreen"

class SLoadingScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SLoadingScreen) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		//Title of your game
		const FText TitleText = LOCTEXT("GameTitle", "Your game title");

		// Path to your game logo image
		const FName LogoImagePath(TEXT("/Game/..."));
		// Size of game logo
		const FVector2D LogoSize(200.0, 100.0);
		// Path to text style, used in game logo
		const FName TitleFontPath(TEXT("/Game/UI/Fonts/..."));

		FSlateFontInfo TitleFont;
		TitleFont.Size = 32;
		TitleFont.FontObject = LoadObject<UObject>(NULL, *TitleFontPath.ToString());

		LoadingScreenBrush = MakeShareable(new FSlateDynamicImageBrush(LogoImagePath, LogoSize));
		LoadingScreenBrush->SetResourceObject(LoadObject<UObject>(NULL, *LogoImagePath.ToString()));

		ChildSlot
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			[
				SNew(SImage)
				.ColorAndOpacity(FColor::Black)
			]
			+ SOverlay::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SVerticalBox)

				+SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(SImage)
					.Image(LoadingScreenBrush.Get())
				]

				+SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Fill)
				[
					SNew(STextBlock)
					.Text(TitleText)
					.ColorAndOpacity(FColor::Purple)
					.Font(TitleFont)
					.Margin(FMargin(0.0, 15.0))
				]

				+SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(SCircularThrobber)
				]
			]
		];
	}

public:
	FSlateBrush* LogoBrush;

private:

	TSharedPtr<FSlateDynamicImageBrush> LoadingScreenBrush;
};

class FLoadingScreenModule : public ILoadingScreen 
{
public:
	virtual void StartupModule() override
	{
		if (IsMoviePlayerEnabled())
		{
			CreateLoadingScreen();
		}

	}

	virtual void CreateLoadingScreen()
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreen.MinimumLoadingScreenDisplayTime = 5.0f;
		LoadingScreen.WidgetLoadingScreen = SNew(SLoadingScreen);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}

	virtual void ShowLoadingScreen(bool bManualStop, float TimeSpan) override
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = !bManualStop;
		LoadingScreen.bWaitForManualStop = bManualStop;
		LoadingScreen.bAllowEngineTick = bManualStop;
		LoadingScreen.MinimumLoadingScreenDisplayTime = TimeSpan;
		LoadingScreen.WidgetLoadingScreen = SNew(SLoadingScreen);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
	
	virtual void CloseLoadingScreen() override
	{
		GetMoviePlayer()->StopMovie();
	}

	virtual bool IsGameModule() const override
	{
		return true;
	}

	
};

IMPLEMENT_GAME_MODULE(FLoadingScreenModule, LoadingScreen);

#undef LOCTEXT_NAMESPACE