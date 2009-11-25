#import "Sparkle/SUUpdater.h"
#import "HTTPPOSTOperation.h"

@interface DPAppDelegate : NSObject {
	NSUserDefaults *defaults;
	NSStatusItem *statusItem;
	IBOutlet NSWindow *mainWindow;
	IBOutlet NSMenu *mainMenu;
	IBOutlet NSMenu *statusItemMenu;
	IBOutlet NSToolbar *toolbar;
	IBOutlet NSView *generalSettingsView;
	IBOutlet NSView *processingSettingsView;
	IBOutlet NSView *advancedSettingsView;
	IBOutlet SUUpdater *updater;
	IBOutlet NSTextField *receiverURL;
	IBOutlet NSMenuItem *pauseMenuItem;
	BOOL openAtLogin,
		showInDock,
		showInMenuBar,
		showQueueCountInMenuBar,
		paused,
		enableThumbnails,
		convertImagesTosRGB,
		enablePngcrush,
		trashAfterSuccessfulUpload;
	NSString *filePrefixMatch;
	ASLLogger *log;
	
	int nCurrOps;
	NSDate *uidRefDate;
	BOOL isObservingDesktop;
	NSMutableDictionary *uploadedScreenshots;
	NSDictionary *knownScreenshotsOnDesktop; // fn => dateModified
	NSString *screenshotLocation; // com.apple.screencapture location
	NSString *cacheDir;
	NSString *thumbCacheDir;
	NSSize thumbSize;
	
	NSImage *iconStandby;
	NSImage *iconPaused;
	NSImage *iconSending;
	NSImage *iconOk;
	NSImage *iconError;
	NSImage *iconSelected;
	NSImage *iconSelectedPaused;
	
	NSImage *iconState; // Current state icon (iconStandby or iconPaused)
	NSImage *icon; // Current icon
}

@property(assign) BOOL openAtLogin, showInDock, showInMenuBar, 
	showQueueCountInMenuBar, paused, convertImagesTosRGB, enablePngcrush,
	trashAfterSuccessfulUpload;

-(void)checkForScreenshotsAtPath:(NSString *)dirpath;
-(NSDictionary *)screenshotsAtPath:(NSString *)dirpath modifiedAfterDate:(NSDate *)lmod;
-(NSDictionary *)screenshotsOnDesktop;
-(void)processScreenshotAtPath:(NSString *)path modifiedAtDate:(NSDate *)dateModified;
/**
 * This keeps state, so be careful when calling since it will return different
 * things for each call (or nil if there are no new files).
 */
-(NSDictionary *)findUnprocessedScreenshotsOnDesktop;

-(IBAction)displayViewForGeneralSettings:(id)sender;
-(IBAction)displayViewForProcessingSettings:(id)sender;
-(IBAction)displayViewForAdvancedSettings:(id)sender;

-(IBAction)orderFrontSettingsWindow:(id)sender;
-(IBAction)enableMenuItem:(id)sender;
-(IBAction)disableMenuItem:(id)sender;
-(IBAction)enableOrDisableMenuItem:(id)sender;
-(IBAction)updateMenuItem:(id)sender;
-(IBAction)saveState:(id)sender;

-(void)updateListOfRecentUploads;

-(void)startObservingDesktop;
-(void)stopObservingDesktop;

-(void)momentarilyDisplayIcon:(NSImage *)icon;
-(void)resetIcon;

-(NSMutableDictionary *)uploadedScreenshotForOperation:(HTTPPOSTOperation *)op;
-(void)vacuumUploadedScreenshots;
-(void)writeThumbnailForScreenshotAtPath:(NSString *)path;
-(BOOL)pngcrushPNGImageAtPath:(NSString *)path brute:(BOOL)brute;

@end
