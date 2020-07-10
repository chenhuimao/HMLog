//
//  ViewController.m
//  HMLogDemo
//
//  Created by CHM on 2020/7/9.
//  Copyright © 2020 chenhuimao. All rights reserved.
//

#import "ViewController.h"
#import "HMLog.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet UILabel *displayLab;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
}

- (IBAction)log1 {
    self.displayLab.text = @"Please check the Xcode console output";
    
    HMLog(self.navigationItem.title);
}

- (IBAction)log2:(UIButton *)btn {
    self.displayLab.text = @"Please check the Xcode console output";

    HMLog(btn, self.view.frame, self.view.tag, self.automaticallyAdjustsScrollViewInsets);
}

- (IBAction)log3:(UIButton *)btn forEvent:(UIEvent *)event {
    self.displayLab.text = @"Please check the Xcode console output";

    char c = '*';
    short s = 1991;
    float f = 3.26;
    bool b = true;

    HMLog(self.view.backgroundColor, self.view.frame, self.view.center,  self.view.bounds.size, self.view.alignmentRectInsets, self.title, self.automaticallyAdjustsScrollViewInsets, self.navigationController, [self class], btn, btn.tag, btn.isHidden, event.timestamp, @selector(viewDidAppear:), @selector(viewDidLoad), @"Copyright (c) 2020 Huimao Chen", c, s, f, b);
}

- (IBAction)print1 {
    self.displayLab.text = @"Please check the Xcode console output";
    HMPrint(self.navigationItem.title);
}

- (IBAction)print2 {
    self.displayLab.text = @"Please check the Xcode console output";

    HMPrint(self.view.bounds.size, self.view.alignmentRectInsets, self.title, self.automaticallyAdjustsScrollViewInsets, self.navigationController, [self class], @selector(viewDidAppear:));
}

- (IBAction)getFormatString1 {
    self.displayLab.text = HMFormatString(self.view.frame, self.view.tag, self.automaticallyAdjustsScrollViewInsets);
}
- (IBAction)getFormatString2 {
    self.displayLab.text = HMFormatString(self.view.frame, self.view.center,  self.view.bounds.size, self.view.alignmentRectInsets, self.title, self.automaticallyAdjustsScrollViewInsets, self.navigationController, [self class], @selector(viewDidAppear:), @"Copyright (c) 2020 Huimao Chen");
}

@end
