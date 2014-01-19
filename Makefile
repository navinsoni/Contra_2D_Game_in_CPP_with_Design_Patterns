
ifeq ("$(shell whoami)", "malloy")
  CXX = clang++
else
  CXX = g++
endif
CXX_LINK = g++

# Warnings frequently signal eventual errors:
CXXFLAGS=`sdl-config --cflags` -g -W -Wall -Weffc++ -Wextra -pedantic -O0
LDFLAGS = `sdl-config --libs` -lSDL_ttf -lSDL_image -lSDL_mixer -lexpat -lcwiid -lbluetooth

OBJS = \
	main.o \
	manager.o \
	spritemanager.o \
	gamedata.o \
	parseXML.o \
	parseLsysXML.o \
	aaline.o \
	lsystem.o \
	clock.o \
	vector2f.o \
	frame.o \
	player.o \
	enemystationary.o \
	framefactory.o \
	sprite.o \
	lsystemSprite.o \
	multiframesprite.o \
	singleframesprite.o \
	world.o \
	viewport.o \
	ioManager.o \
	bar.o \
	introduction.o \
	sound.o \
	bullets.o \
	bullet.o \
	mapx.o \
	collisionStrategy.o \
	explodingSprite.o \
	chunk.o \
	text.o \
	boxtarget.o \
	bigbullet.o \
	flame.o \
	enemyFinal1.o \
	menu.o \
	name.o \
	scrolling.o \
	scrollingline.o \
	musicvalue.o \
	soundvalue.o \
	help.o \
	wiimote.o \
	wiimenu.o \
	redorb.o

EXEC = run

# $< refers to the first dependency
%.o: %.cpp
	$(CXX_LINK) $(CXXFLAGS) -c $< -o $@

# $@ refers to the target
$(EXEC): $(OBJS)
	g++ $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

main.o: main.cpp
manager.o: manager.cpp manager.h ioManager.h clock.h framefactory.h world.h spritemanager.h
spritemanager.o: spritemanager.cpp spritemanager.h framefactory.h viewport.h sprite.h player.h enemystationary.h lsystemSprite.h
ioManager.o: ioManager.cpp ioManager.h
parseXML.o: parseXML.cpp parseXML.h
gamedata.o: gamedata.cpp gamedata.h parseXML.h
parseLsysXML.o: parseLsysXML.cpp parseLsysXML.h
aaline.o: aaline.cpp aaline.h
lsystem.o: lsystem.cpp lsystem.h ioManager.h parseLsysXML.h
clock.o: clock.cpp clock.h
vector2f.o: vector2f.cpp vector2f.h
frame.o: frame.cpp frame.h
framefactory.o: framefactory.cpp framefactory.h ioManager.h gamedata.h frame.h
frame.o: frame.cpp frame.h ioManager.h
player.o: player.cpp player.h multiframesprite.h frame.h framefactory.h gamedata.h
enemystationary.o: enemystationary.cpp enemystationary.h multiframesprite.h frame.h framefactory.h
sprite.o: sprite.cpp sprite.h drawable.h frame.h framefactory.h
lsystemSprite.o: lsystemSprite.cpp lsystemSprite.h sprite.h drawable.h frame.h
multiframesprite.o: multiframesprite.cpp multiframesprite.h sprite.h frame.h framefactory.h gamedata.h
singleframesprite.o: singleframesprite.cpp singleframesprite.h sprite.h frame.h framefactory.h gamedata.h
world.o: world.cpp world.h
viewport.o: viewport.cpp viewport.h
redorb.o: redorb.cpp redorb.h singleframesprite.h frame.h framefactory.h gamedata.h
bar.o: bar.cpp bar.h singleframesprite.h frame.h framefactory.h gamedata.h aaline.h
introduction.o: introduction.cpp introduction.h
combine.o: combine.cpp combine.h
sound.o: sound.cpp sound.h
bullets.o: bullets.cpp bullets.h
bullet.o: bullet.cpp bullet.h
collisionStrategy.o: collisionStrategy.cpp collisionStrategy.h
mapx.o: mapx.cpp mapx.h
explodingSprite.o: explodingSprite.cpp explodingSprite.h
chunk.o: chunk.cpp chunk.h
text.o: text.cpp text.h
boxtarget.o: boxtarget.cpp boxtarget.h
bigbullet.o: bigbullet.cpp bigbullet.h
flame.o: flame.cpp flame.h
enemyFinal1.o: enemyFinal1.cpp enemyFinal1.h
menu.o: menu.cpp menu.h
name.o: name.cpp name.h
scrolling.o: scrolling.cpp scrolling.h
scrollingline.o: scrollingline.cpp scrollingline.h
musicvalue.o: musicvalue.cpp musicvalue.h
soundvalue.o: soundvalue.cpp soundvalue.h
help.o: help.cpp help.h
wiimote.o: wiimote.cpp wiimote.h
wiimenu.o: wiimenu.cpp wiimenu.h

clean:
	rm -rf $(OBJS)
	rm -rf $(EXEC)
