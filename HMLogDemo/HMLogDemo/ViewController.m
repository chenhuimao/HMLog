// The MIT License (MIT)
//
// Copyright (c) 2020 Huimao Chen
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


// You can define HMPrintEnable macro before import HMLog.h
#ifdef DEBUG
#define HMPrintEnable 1
#else
#define HMPrintEnable 0
#endif

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
    SEL mySEL = @selector(viewWillAppear:);

    HMLog(self.view.backgroundColor, self.view.frame, self.view.center,  self.view.bounds.size, self.view.alignmentRectInsets, self.title, self.automaticallyAdjustsScrollViewInsets, self.navigationController, [self class], btn, btn.tag, btn.isHidden, event.timestamp, mySEL, @selector(viewDidLoad), @"Copyright (c) 2020 Huimao Chen", c, s, f, b);
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
