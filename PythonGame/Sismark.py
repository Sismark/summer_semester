import sys,random,math,pygame #将pygame库导入python
from pygame.locals import *  #引入pygame中的常量
from Game_Paint import *
figure_image_DOWN=['a/a1.png','a/a2.png','a/a3.png','a/a4.png','a/a5.png','a/a6.png']
figure_image_UP=['b/b1.png','b/b2.png','b/b3.png','b/b4.png','b/b5.png','b/b6.png','b/b7.png','b/b8.png']
figure_image_LEFT=['c/c1.png','c/c2.png','c/c3.png','c/c4.png','c/c5.png','c/c6.png','c/c7.png']
figure_image_RIGHT=['d/d1.png','d/d2.png','d/d3.png','d/d4.png','d/d5.png','d/d6.png','d/d7.png','d/d8.png']
bomb_image=['e/e1.png','e/e2.png','e/e3.png','e/e4.png','e/e5.png','e/e6.png','e/e7.png']
Bombs=[ ]
######################炸弹类#################
class Bomb(pygame.sprite.Sprite):
    def __init__(self,first_location):
        pygame.sprite.Sprite.__init__(self)
        self.image = pygame.image.load("boow.png").convert_alpha()
        self.image=pygame.transform.smoothscale(self.image,(35,20))
        self.rect = self.image.get_rect()
        self.rect.center=first_location
        self.bomb=0
        self.timer=0
    def Boow(self,bomb_flag,Map):
        if bomb_flag==1:
            self.timer+=1
            center = self.rect.center
            if self.bomb>6:
                self.bomb=0
            self.image = pygame.image.load(bomb_image[self.bomb]).convert_alpha()
            self.image=pygame.transform.smoothscale(self.image,(60,40))
            self.rect = self.image.get_rect()
            self.rect.center = center
            if self.timer>7:
                self.bomb += 1
                self.timer=0
            for y in range(14):
                for x in range(19):
                    if 0<=Map[y][x] <= 5 or Map[y][x]==19:
                            if  (140+y*40)<(self.rect.centery+30)<(180+y*40) and (60+x*60)< self.rect.centerx<(120+x*60) :
                                Map[y][x]=6
                            if  (140+y*40)<(self.rect.centery-30)<(180+y*40) and (60+x*60)< self.rect.centerx<(120+x*60) :
                                Map[y][x]=6
                            if (140+y*40)<self.rect.centery<(180+y*40) and (60+x*60)< (self.rect.centerx+45)<(120+x*60) :
                                Map[y][x]=6
                            if (140+y*40)<self.rect.centery<(180+y*40) and (60+x*60)< (self.rect.centerx-45)<(120+x*60) :
                                Map[y][x]=6                                
##################精灵类#######################
class Figure(pygame.sprite.Sprite):
    def __init__(self):
        pygame.sprite.Sprite.__init__(self)
        self.image = pygame.image.load("a/a0.png").convert_alpha()
        self.image=pygame.transform.smoothscale(self.image,(35,20))
        self.rect = self.image.get_rect()
        self.rect.center=first_location
        #self.is_hit = False
        self.speed = 2
        self.down = 0
        self.left = 0
        self.right = 0
        self.up = 0
        self.timer=0
        self.die=0
        self.win=0
        self.win_flag=0
    def turn(self,distance):
        center = self.rect.center
        if distance==2:
            self.timer+=1
            if self.down>5:
                self.down=0
            self.image = pygame.image.load(figure_image_DOWN[self.down]).convert_alpha()
            self.image=pygame.transform.smoothscale(self.image,(35,20))
            self.rect = self.image.get_rect()
            self.rect.center = center
            if self.timer>12:
                self.down += 1
                self.timer=0

        if distance==0:
            self.timer+=1
            if self.left >6:
                self.left =0
            self.image = pygame.image.load(figure_image_LEFT[self.left]).convert_alpha()
            self.image=pygame.transform.smoothscale(self.image,(35,20)) 
            self.rect = self.image.get_rect()
            self.rect.center = center
            if self.timer>12:
                self.left  += 1
                self.timer=0

        if distance==3:
            self.timer+=1
            if self.up >7:
                self.up =0
            self.image = pygame.image.load(figure_image_UP[self.up]).convert_alpha()
            self.image=pygame.transform.smoothscale(self.image,(35,20))
            self.rect = self.image.get_rect()
            self.rect.center = center
            if self.timer>12:
                self.up  += 1
                self.timer=0

        if distance==1:
            self.timer+=1
            if self.right >7:
                self.right =0
            self.image = pygame.image.load(figure_image_RIGHT[self.right]).convert_alpha()
            self.image=pygame.transform.smoothscale(self.image,(35,20))
            self.rect = self.image.get_rect()
            self.rect.center = center
            if self.timer>12:
                self.right  += 1
                self.timer=0

    def moved(self,temper,barrier):
        flag=0
        if temper==0 :
            if self.rect.centerx<=90 :
                self.rect.centerx=self.rect.centerx
            elif self.rect.centerx>90 :
                for y in range(14):
                    for x in range(19):
                        if 0<=Map[y][x] <= 5 or Map[y][x] == 20 :
                            if (60+60*x)<(self.rect.centerx-15)<(120+60*x) and (140+y*40)<(self.rect.centery+10)<(180+y*40) :
                                self.rect.centerx=self.rect.centerx
                                flag=1
                            if (60+60*x)<(self.rect.centerx-15)<(120+60*x) and (140+y*40)<(self.rect.centery-10)<(180+y*40) :
                                self.rect.centerx=self.rect.centerx
                                flag=1  
                        if Map[y][x] == 19:
                            self.win+=1
                            if (75+60*x)<(self.rect.centerx-15)<(105+60*x) and (150+y*40)<(self.rect.centery+10)<(170+y*40) :
                                self.die=1
                            if (75+60*x)<(self.rect.centerx-15)<(105+60*x) and (150+y*40)<(self.rect.centery-10)<(170+y*40) :
                                self.die=1
                        if Map[y][x] !=19:
                            self.win-=1
                self.win_flag=1
                if flag==0:
                    self.rect.centerx -= self.speed
                    
        if temper==1:
            if self.rect.centerx>=1170 :
                self.rect.centerx=self.rect.centerx
            elif self.rect.centerx<=1170 :
                for y in range(14):
                    for x in range(19):
                        if 0<=Map[y][x] <= 5 or Map[y][x] == 20:
                            if (60+60*x)<=(self.rect.centerx+15)<=(120+60*x) and (140+y*40)<=(self.rect.centery+10)<=(180+y*40) :
                                self.rect.centerx=self.rect.centerx
                                flag=1
                            if (60+60*x)<=(self.rect.centerx+15)<=(120+60*x) and (140+y*40)<=(self.rect.centery-10)<=(180+y*40) :
                                self.rect.centerx=self.rect.centerx
                                flag=1                       
                        if Map[y][x] == 19:
                            if (75+60*x)<=(self.rect.centerx+15)<=(105+60*x) and (150+y*40)<=(self.rect.centery+10)<=(170+y*40) :
                                self.die=1
                            if (75+60*x)<=(self.rect.centerx+15)<=(105+60*x) and (150+y*40)<=(self.rect.centery-10)<=(170+y*40) :
                                self.die=1
                if flag==0:
                    self.rect.centerx += self.speed
                    
        if temper==3:
            if self.rect.centery<=160:
                self.rect.centery=self.rect.centery
            elif self.rect.centery>160:
                for y in range(14):
                    for x in range(19):
                        if 0<=Map[y][x] <= 5 or Map[y][x] == 20:
                            if (60+60*x)<=(self.rect.centerx-15)<=(120+60*x) and (140+y*40)<=(self.rect.centery-10)<=(180+y*40) :
                                self.rect.centerx=self.rect.centerx
                                flag=1
                            if (60+60*x)<=(self.rect.centerx+15)<=(120+60*x) and (140+y*40)<=(self.rect.centery-10)<=(180+y*40) :
                                self.rect.centerx=self.rect.centerx
                                flag=1  
                        if Map[y][x] == 19:
                            if (75+60*x)<=(self.rect.centerx-15)<=(105+60*x) and (150+y*40)<=(self.rect.centery-10)<=(170+y*40) :
                                self.die=1
                            if (75+60*x)<=(self.rect.centerx+15)<=(105+60*x) and (150+y*40)<=(self.rect.centery-10)<=(170+y*40) :
                                self.die=1
                if flag==0:
                    self.rect.centery -= self.speed

        if temper==2:
            if self.rect.centery>=680:
                self.rect.centery=self.rect.centery
            elif self.rect.centery<680:
                for y in range(14):
                    for x in range(19):
                        if 0<=Map[y][x] <= 5 or Map[y][x] == 20:
                            if (60+60*x)<=(self.rect.centerx-15)<=(120+60*x) and (140+y*40)<=(self.rect.centery+10)<=(180+y*40) :
                                self.rect.centerx=self.rect.centerx
                                flag=1
                            if (60+60*x)<=(self.rect.centerx+15)<=(120+60*x) and (140+y*40)<=(self.rect.centery+10)<=(180+y*40) :
                                self.rect.centerx=self.rect.centerx
                                flag=1
                        if Map[y][x] == 19:
                            if (75+60*x)<=(self.rect.centerx-15)<=(105+60*x) and (150+y*40)<=(self.rect.centery+10)<=(170+y*40) :
                                self.die=1
                            if (75+60*x)<=(self.rect.centerx+15)<=(105+60*x) and (150+y*40)<=(self.rect.centery+10)<=(170+y*40) :
                                self.die=1
                if flag==0:
                    self.rect.centery += self.speed
    def boow(self):
        bomb=Bomb(self.rect.center)
        Bombs.append(bomb)
################################################
pygame.init() #初始化pygame
pygame.display.list_modes()
#先创建窗口
Width=1260
Height=740
screen=pygame.display.set_mode((Width,Height),0,32)
Fullscreen=False
GameStart=False
#FULLSCREEN全屏窗口
#NOFRAME无边框窗口
#RESIZABLE创建一个可以改变大小的窗口
clock=pygame.time.Clock()
pygame.display.set_caption("Sismark")#窗口签名
font=pygame.font.Font(None,18)#创建字体对象
gameover=pygame.font.Font(None,100)
over_image=gameover.render("Game Over",True,(255,255,255))
x,y=60,140
start=pygame.image.load("start.png").convert()#加载位图
start=pygame.transform.scale(start,(Width,Height))#缩放
die=pygame.image.load("die.png").convert_alpha()#加载位图
die=pygame.transform.scale(die,(500,500))#缩放
##音乐
pygame.mixer.init()
pygame.mixer.music.load("music.ogg")
pygame.mixer.music.set_volume(0.3)
pygame.mixer.music.play(-1)
bomb_music=pygame.mixer.Sound("sound.ogg")
bomb_music.set_volume(10)
##
w,h = 19,14
Map = list(list(20 if i%2 and j%2  else 6 if i+j<=1 else random.randint(0,19)  for j in range(w))  for i in range(h))
turn,move=5,5
first_location=[90,160]
figure=Figure()
Flag=0
bomb_Flag=0
refresh_flag=0
while True:
    clock.tick(60)
    for event in pygame.event.get():
        if not GameStart:
            screen.blit(start,(0,0))
        if event.type == QUIT:
            pygame.quit()
            sys.exit()
        if event.type==KEYDOWN:
            if event.key==K_a:
                pygame.quit()
                sys.exit()
            if event.key==K_b:
                GameStart=not GameStart
            if event.key==K_f:
            #设置可切换大小的窗口
                Fullscreen=not Fullscreen
                if Fullscreen:
                    screen=pygame.display.set_mode((Width,Height),0,32)
                else:
                    screen=pygame.display.set_mode((Width,Height),FULLSCREEN,32)
            if event.key==K_RIGHT:            
                turn=1
                move=1
            if event.key==K_LEFT:            
                turn=0
                move=0
            if event.key==K_UP:            
                turn=3
                move=3
            if event.key==K_DOWN:            
                turn=2
                move=2
            if event.key==K_z and Flag!=1:
                Flag=1
                figure.boow()
            if event.key==K_x and Flag==1:
                bomb_music.play()
                bomb_Flag=1
                Flag=0
    if event.type==KEYUP:
        turn=5
        move=5
    if turn<5 and move<5:
        figure.turn(turn)
        figure.moved(move,Map)
    if GameStart and figure.die ==0:
        MoveMonster(Map)
        GamePaint(screen,Map,x,y)      
        screen.blit(figure.image,figure.rect)
        #pygame.draw.rect(screen,(255,255,255),figure.rect,1)
        if Flag==1:
            for bomb in Bombs:
                screen.blit(bomb.image,bomb.rect)
        if bomb_Flag==1:
            refresh_flag+=1
            bomb.Boow(bomb_Flag,Map)
            screen.blit(bomb.image,bomb.rect)
            if refresh_flag>50:
                bomb_Flag=0
                refresh_flag=0
    if figure.die==1 :
        screen.blit(die,(380,170))
        screen.blit(over_image,(440,120))
    if figure.win==0 and figure.win_flag==1:
        screen.blit(die,(380,170))
        screen.blit(over_image,(440,120))    
    pygame.display.update()
            
