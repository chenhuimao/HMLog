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

// You can define HMLogTypeExtension macro before import HMLog.h
#define HMLogTypeExtension \
        else if (strcmp(type, @encode(CGVector)) == 0) { \
            CGVector actual = (CGVector)va_arg(v, CGVector); \
            obj = NSStringFromCGVector(actual); \
        } else if (strcmp(type, @encode(CLLocationCoordinate2D)) == 0) { \
            CLLocationCoordinate2D actual = (CLLocationCoordinate2D)va_arg(v, CLLocationCoordinate2D); \
            obj = [NSString stringWithFormat:@"latitude: %lf, longitude: %lf", actual.latitude, actual.longitude]; \
        }

#import "CustomizeFormatViewController.h"
#import <CoreLocation/CoreLocation.h>
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

    CGVector vector = CGVectorMake(110, 119);
    CLLocationCoordinate2D coordinate = CLLocationCoordinate2DMake(22.512145, 113.9155);
    HMLog(self.view.backgroundColor, self.view.frame, self.view.center, vector, coordinate);
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
