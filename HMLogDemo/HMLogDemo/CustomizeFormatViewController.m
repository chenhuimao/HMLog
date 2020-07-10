//
//  CustomizeFormatViewController.m
//  HMLogDemo
//
//  Created by CHM on 2020/7/10.
//  Copyright © 2020 chenhuimao. All rights reserved.
//

// You can define HMLogPrefix macro before import HMLog.h
#define HMLogPrefix(INDEX, VAR) \
        HMStringify(INDEX:)
// No Prefix format
//#define HMLogPrefix(INDEX, VAR) ""

// You can define HMLogHeaderFormatString macro before import HMLog.h
#define HMLogHeaderFormatString(FUNC, LINE) \
        [NSString stringWithFormat:@"----[%d]???????????[%d]----\n", LINE, LINE]
// Just the dividing line
//#define HMLogHeaderFormatString(FUNC, LINE) \
//        [NSString stringWithFormat:@"*******************\n"]

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
