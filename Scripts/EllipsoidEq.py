# Created by steve on 17-10-27 上午9:47
'''
                   _ooOoo_ 
                  o8888888o 
                  88" . "88 
                  (| -_- |) 
                  O\  =  /O 
               ____/`---'\____ 
             .'  \\|     |//  `. 
            /  \\|||  :  |||//  \ 
           /  _||||| -:- |||||-  \ 
           |   | \\\  -  /// |   | 
           | \_|  ''\---/''  |   | 
           \  .-\__  `-`  ___/-. / 
         ___`. .'  /--.--\  `. . __ 
      ."" '<  `.___\_<|>_/___.'  >'"". 
     | | :  `- \`.;`\ _ /`;.`/ - ` : | | 
     \  \ `-.   \_ __\ /__ _/   .-` /  / 
======`-.____`-.___\_____/___.-`____.-'====== 
                   `=---=' 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ 
         佛祖保佑       永无BUG 
'''

import numpy as np

class EllipsoidEq:
    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def errorFunction(self, para):
        result = ((self.x - para[0]) ** 2.0) / (para[1]**2.0) + \
                 ((self.y - para[2]) ** 2.0) / (para[3]**2.0) + \
                 ((self.z - para[4]) ** 2.0) / (para[5]**2.0) - 1.0
        return np.abs(result).sum()