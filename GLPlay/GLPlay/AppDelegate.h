//
//  AppDelegate.h
//  GLPlay
//
//  Created by nsp on 26/04/2014.
//  Copyright (c) 2014 tujv.net. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "OpenGLView.h"


@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@property (nonatomic, retain) IBOutlet OpenGLView *glView;

@end

