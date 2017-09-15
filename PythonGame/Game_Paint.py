import sys,random,math,pygame #将pygame库导入python
from pygame.locals import *  #引入pygame中的常量
monster_image=['m1.png','m2.png','m3.png']
pygame.init()#初始化
Time=18000
monster_flag=0
monster_frame=0
monster_number=0
flag=0
num=0
score=0
move_flag=0
def GamePaint(screen,Map,figure_x,figure_y):
    global Time,monster_image,monster_frame,monster_flag,monster_number,num,flag,score
    monster_flag+=1
    if monster_flag>30:
        monster_frame+=1
        if monster_frame>2:
            monster_frame=0
        monster_flag=0
    Time-=1
    Background=(34,139,34)
    white=(255,255,255)
    BLOCK_width = 60
    BLOCK_height=40
    ##

    ##
    ###################记分版######################
    Scoreboard=100
    Font_time=pygame.font.Font(None,50)
    Font_score=pygame.font.Font(None,50)
    if num>1 and num>monster_number:
        score=num-monster_number
    monster_number=0
    ScoreImage=Font_score.render("Score  "+str(score*100),True,white)
    TimeImage=Font_time.render("Time  "+str(Time//60),True,white)
    ##############################################
    Boundry=BLOCK_height+Scoreboard
    Width=1260
    Height=740-Scoreboard
    monster=pygame.image.load(monster_image[monster_frame]).convert_alpha()
    wallA=pygame.image.load("wallA.png").convert()
    brick = pygame.image.load("brick.png").convert()
    monster=pygame.transform.smoothscale(monster,(BLOCK_width,BLOCK_height))
    wallA=pygame.transform.smoothscale(wallA,(BLOCK_width,BLOCK_height))
    brick=pygame.transform.smoothscale(brick,(BLOCK_width,BLOCK_height))
    if True:
        screen.fill(Background)
        pygame.draw.rect(screen,(192,192,192),(0,0,1260,Scoreboard),0)
        screen.blit(TimeImage,(340,40))
        screen.blit(ScoreImage,(800,40))
        h = len(Map)
        w = len(Map[0])
        for y in range(h):
            for x in range(w):
                value = Map[y][x]
                if 0<=value <= 5:
                    image = brick
                elif value == 20:
                    image = wallA
                elif value == 19:
                    monster_number+=1
                    image = monster
                if 0<=value <= 5 or value == 20 or value == 19:
                    screen.blit(image,(BLOCK_width+x*BLOCK_width,Boundry+y*BLOCK_height))                 
        if flag==0:
            num=monster_number
            flag=1
        for y in range(h+2):
            for x in range(w+2):
                if y==0 or y==15 or x==0 or x==20:
                    screen.blit(wallA,(x*BLOCK_width,Scoreboard+y*BLOCK_height))
                                      
    return;
def MoveMonster(Map):
    global move_flag
    move_flag+=1
    if move_flag>30:
        move_flag=0    
        monster_to_move=[ ]
        for y in range(14):
            for x in range(19):
                if Map[y][x]==19:
                    Map[y][x]=6
                    monster_to_move.append((x,y))
        for x,y in monster_to_move:
            dirs= []
            if y>=1 and 6<=Map[y-1][x]<=18:
                dirs.append('W')
            if y<=12 and 6<=Map[y+1][x]<=18:
                dirs.append('S')
            if x>=1 and 6<=Map[y][x-1]<=18:
                dirs.append('A')
            if x<=17 and 6<=Map[y][x+1]<=18:
                dirs.append('D')
            Max=len(dirs)-1
            if Max>0:
                d=dirs[random.randint(0,Max)]
                if d=='W':
                    y-=1
                elif d=='S':
                    y+=1
                elif d=='A':
                    x-=1
                elif d=='D':
                    x+=1
            Map[y][x]=19
