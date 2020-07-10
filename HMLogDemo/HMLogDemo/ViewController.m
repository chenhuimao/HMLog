//
//  ViewController.m
//  HMLogDemo
//
//  Created by CHM on 2020/7/9.
//  Copyright © 2020 chenhuimao. All rights reserved.
//

#import "ViewController.h"
#import "HMLog.h"

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
}

- (IBAction)log1 {
    HMLog(self.navigationItem.title);
}

- (IBAction)log2:(UIButton *)btn {
    HMLog(btn, self.view.frame, self.view.tag, self.automaticallyAdjustsScrollViewInsets);
}

- (IBAction)log3:(UIButton *)btn forEvent:(UIEvent *)event {
    char c = '*';
    short s = 1991;
    float f = 3.26;
    bool b = true;

    HMLog(self.view.backgroundColor, self.view.frame, self.view.center,  self.view.bounds.size, self.view.alignmentRectInsets, self.title, self.automaticallyAdjustsScrollViewInsets, self.navigationController, [self class], btn, btn.tag, btn.isHidden, event.timestamp, @selector(viewDidAppear:), @selector(viewDidLoad), @"Copyright (c) 2020 Huimao Chen", c, s, f, b);
}


@end
