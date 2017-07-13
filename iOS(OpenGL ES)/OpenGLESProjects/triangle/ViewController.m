//
//  ViewController.m
//  Triangle
//
//  Created by wei shi on 2017/7/13.
//  Copyright © 2017年 wei shi. All rights reserved.
//

#import "ViewController.h"
#import "TFTriangleDemoView.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self showTriangle];
}

-(void)showTriangle{
    TFTriangleDemoView *renderView = [[TFTriangleDemoView alloc] initWithFrame:self.view.bounds];
    [self.view addSubview:renderView];
}


@end
