//
//  CustomizeFormatViewController.m
//  HMLogDemo
//
//  Created by CHM on 2020/7/10.
//  Copyright © 2020 chenhuimao. All rights reserved.
//

// You can define HMLogFormat macro before import HMLog.h
#define HMLogFormat(INDEX, VAR) \
        , HMStringify(INDEX:), @encode(__typeof__(VAR)), (VAR)

// No Prefix format
//#define HMLogFormat(INDEX, VAR) \
//        , "", @encode(__typeof__(VAR)), (VAR)

#import "CustomizeFormatViewController.h"
#import "HMLog.h"

@interface CustomizeFormatViewController ()
@property (weak, nonatomic) IBOutlet UILabel *displayLab;
@end

@implementation CustomizeFormatViewController

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (IBAction)log {
    self.displayLab.text = @"Please check the Xcode console output";

    HMLog(self.view.backgroundColor, self.view.frame, self.view.center);
}

- (IBAction)print {
    self.displayLab.text = @"Please check the Xcode console output";

    HMPrint(self.automaticallyAdjustsScrollViewInsets, self.navigationController, [self class], @selector(viewDidLoad), self.view.tag);

}
- (IBAction)getFormatString {
    SEL mySEL = @selector(viewDidLoad);
    self.displayLab.text = HMFormatString(self.view.frame, self.view.center,  self.view.bounds.size, self.view.alignmentRectInsets, self.title, [self class], mySEL, @"Copyright (c) 2020 Huimao Chen");
}

@end
