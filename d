[1mdiff --git a/src/Client/GameScene.h b/src/Client/GameScene.h[m
[1mindex 94c1a98..f4708e9 100644[m
[1m--- a/src/Client/GameScene.h[m
[1m+++ b/src/Client/GameScene.h[m
[36m@@ -3,7 +3,7 @@[m
 [m
 #include "SdlWindow.h"[m
 #include "SdlTexture.h"[m
[31m-#include "BackgroundView.h"[m
[32m+[m[32m#include "View/BackgroundView.h"[m
 #include "InputHandler.h"[m
 #include "TextureCreator.h"[m
 #include "BaseScene.h"[m
[1mdiff --git a/src/Client/TextureCreator.cpp b/src/Client/TextureCreator.cpp[m
[1mindex 65f6599..3f2dca5 100644[m
[1m--- a/src/Client/TextureCreator.cpp[m
[1m+++ b/src/Client/TextureCreator.cpp[m
[36m@@ -2,14 +2,14 @@[m
 #include <iostream>[m
 #include "../Common/Constants.h"[m
 [m
[31m-#include "StraightTrackView.h"[m
[31m-#include "CurveTrackView.h"[m
[31m-#include "HealthPowerupView.h"[m
[31m-#include "BoostPowerupView.h"[m
[31m-#include "RockView.h"[m
[31m-#include "CarView.h"[m
[31m-#include "OilView.h"[m
[31m-#include "MudView.h"[m
[32m+[m[32m#include "View/StraightTrackView.h"[m
[32m+[m[32m#include "View/CurveTrackView.h"[m
[32m+[m[32m#include "View/HealthPowerupView.h"[m
[32m+[m[32m#include "View/BoostPowerupView.h"[m
[32m+[m[32m#include "View/RockView.h"[m
[32m+[m[32m#include "View/CarView.h"[m
[32m+[m[32m#include "View/OilView.h"[m
[32m+[m[32m#include "View/MudView.h"[m
 [m
 TextureCreator::TextureCreator(const SdlWindow& window) :[m
 	straightTrackTex("straight_track.png", window),[m
[1mdiff --git a/src/Client/TextureCreator.h b/src/Client/TextureCreator.h[m
[1mindex f784cfb..4b04295 100644[m
[1m--- a/src/Client/TextureCreator.h[m
[1m+++ b/src/Client/TextureCreator.h[m
[36m@@ -4,7 +4,7 @@[m
 #include "SdlWindow.h"[m
 #include <memory>[m
 #include "SdlTexture.h"[m
[31m-#include "ObjectView.h"[m
[32m+[m[32m#include "View/ObjectView.h"[m
 [m
 typedef std::shared_ptr<ObjectView> ObjectViewPtr;[m
 [m
[1mdiff --git a/src/Client/View/ObjectView.h b/src/Client/View/ObjectView.h[m
[1mindex 0dd6e9a..f62bd46 100644[m
[1m--- a/src/Client/View/ObjectView.h[m
[1m+++ b/src/Client/View/ObjectView.h[m
[36m@@ -1,8 +1,8 @@[m
 #ifndef OBJECT_VIEW[m
 #define OBJECT_VIEW[m
 [m
[31m-#include "Area.h"[m
[31m-#include "SdlTexture.h"[m
[32m+[m[32m#include "../Area.h"[m
[32m+[m[32m#include "../SdlTexture.h"[m
 #include <vector>[m
 [m
 class ObjectView {[m
