/*
* Descent 3 
* Copyright (C) 2024 Parallax Software
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.

--- HISTORICAL COMMENTS FOLLOW ---

 * $Logfile: /DescentIII/main/AImain.cpp $
 * $Revision: 479 $
 * $Date: 4/19/00 5:08p $
 * $Author: Matt $
 *
 * The Main of the AI code.
 *
 * $Log: /DescentIII/main/AImain.cpp $
 *
 * 479   4/19/00 5:08p Matt
 * From Duane for 1.4
 * Added checks, asserts, and fixes for bad return values
 * Added error checking and minor optimization
 *
 * 478   3/20/00 12:00p Matt
 * Merge of Duane's post-1.3 changes.
 * Bail from anim update if no anim data.
 *
 * 477   11/02/99 12:17p Chris
 * Improved the targetting code (no max dist when in the same room as
 * target)
 *
 * 476   10/24/99 10:46p Chris
 * Added the target_died notification
 *
 * 475   10/23/99 2:43a Chris
 * Added the PutObjectOnObject AI Goal
 *
 * 474   10/22/99 10:43p Jeff
 * put in check to handle new code from mac
 *
 * 473   10/22/99 3:40p Kevin
 * Mac merge fixes
 *
 * 472   10/21/99 2:12p Matt
 * Mac merge
 *
 * 471   10/20/99 5:40p Chris
 * Added the Red Guidebot
 *
 * 470   10/17/99 11:58p Chris
 * Improved the hearing/seeing code, Added AIN_FIRED_WEAPON notify, and
 * added a *hack* so that the final boss could fire his weapons during a
 * cutscene...  (usually this is a no-no).
 *
 * 469   10/08/99 4:53p Nate
 * Added ability to disable individual melee attacks
 *
 * 468   10/08/99 4:14p 3dsmax
 * creeper fix (attached objs and FOV) (chris)
 *
 * 467   7/27/99 6:39p Chris
 * Turned off the GB's player weapon dodging when he is in RTYPE mode
 *
 * 466   7/27/99 4:20p Chris
 * Improved GB avoidance code
 *
 * 465   7/26/99 3:52p Chris
 * Wall pulsing for the GB
 *
 * 464   7/26/99 1:18p Chris
 * He now only dodges player shots
 *
 * 463   7/26/99 1:16p Chris
 * GB now dodges player (and targetted robot) shots
 *
 * 462   5/24/99 3:23p Chris
 * Fixed team anarchy bug.
 *
 * 461   5/23/99 10:39p Chris
 * Fixed client gunboys so they not fire at the server
 *
 * 460   5/23/99 5:37a Chris
 * Fixed bugs with non-AIF_DODGE objects dodging.  Made stopping
 * tolerances bigger
 *
 * 459   5/23/99 12:35a Chris
 * Fixed the stop exactly problems
 *
 * 458   5/21/99 7:45p Chris
 * Tweaked the cdist code...  (again)
 *
 * 457   5/21/99 6:01p Chris
 * Fixed turret speed scaling problems
 *
 * 456   5/21/99 7:29a Chris
 * More tweaking...
 *
 * 455   5/20/99 3:48p Chris
 * Rebel stuff isn't usually scaled by diff anymore
 *
 * 454   5/20/99 1:44a Chris
 * Improved scaling of velocity for walkers (I.e. dont scale max speed or
 * rotational speed because it make them look slow and dumb)
 *
 * 453   5/20/99 1:15a Chris
 * Improved BNode Path Following for end points on the path.  Fixed bugs
 * with non-auto targetting
 *
 * 452   5/19/99 2:16a Chris
 * Fixed gunboys in coop (will not fire on teammates now)
 *
 * 451   5/18/99 10:54p Chris
 * Added some ASSERTs
 *
 * 450   5/18/99 6:58p Chris
 * Hmmmm....  Not sure how that crash happened
 *
 * 449   5/18/99 10:57a Chris
 * Various bug fixes
 *
 * 448   5/17/99 6:06p Chris
 * Adding robot debug code
 *
 * 447   5/12/99 11:15p Chris
 * Adjusted fvi_find for vis.
 *
 * 446   5/12/99 6:18a Chris
 * Vastly improved FindObjOfType.  Ignores non-rendered objects, if type
 * is robot it ignores cameras, dead robots, or robots without any
 * gunpoints (like a mine).
 *
 * 445   5/11/99 5:49p Chris
 * Scaled energy drain by diff level...  Increased HotShot energy drain,
 * Fixed problem with Thief sound getting muffled by melee hit sound
 *
 * 444   5/10/99 5:11p Chris
 * Fixed another hearing/seeing bug
 *
 * 443   5/10/99 2:59p Chris
 * Fixed fov bug
 *
 * 442   5/10/99 8:21a Chris
 * Reduced wall collision size for GB
 *
 * 441   5/10/99 12:23a Chris
 * Fixed another hearing/seeing case.  :)  Buddy bot now is in the player
 * ship at respawn
 *
 * 440   5/09/99 8:11p Chris
 * Made the whole see/hear distintion work (mostly)
 *
 * 439   5/08/99 10:38p Chris
 * Further scaled the game.  :)
 *
 * 438   5/08/99 6:18p Chris
 * Fixed up no hearing cases
 *
 * 437   5/08/99 4:12p Chris
 * Added AI hearing noises... version 1
 *
 * 436   5/07/99 10:56p Chris
 * GB avoids forcefields, lava, and volatile surfaces...  If he accidently
 * hits one of these, he ignores the collision (i.e. no effects).  It make
 * him look smarter.
 *
 * 435   5/07/99 9:33p Chris
 * Improve wall avoidance when never volatile, lava, and water surfaces
 *
 * 434   5/07/99 1:43p Chris
 * Made in-game cinematics use the ORIENT_PATH_NODE for player ships
 *
 * 433   5/07/99 11:51a Chris
 * Improve the algorithm for zero awareness firing
 *
 * 432   5/07/99 11:24a Chris
 * Made 0 agresion robots only fire when they have a clear shot
 *
 * 431   5/04/99 6:49p Jason
 * fixed dumb bug with spray weapons
 *
 * 430   5/02/99 1:59a Jason
 * possibly fixed a bug related to spray weapons and dying
 *
 * 429   5/01/99 3:49a Chris
 * Added the "No scale movement properties by diff level" checkbox
 *
 * 428   5/01/99 2:21a Chris
 * Use the GF_SPEED_XXX  stuff
 *
 * 427   4/30/99 2:09a Chris
 * Gunboys will not target triggers anymore
 *
 * 426   4/29/99 3:59p Chris
 * Fixed AI_SEE_SOUND playing too often (like all the time...)
 *
 * 425   4/27/99 4:41a Jeff
 * only create guidebots if a single player game, or if its a multiplayer
 * game and the correct netflag is set
 *
 * 424   4/26/99 11:11a Chris
 * Updated Bnode system
 *
 * 423   4/24/99 2:20a Chris
 * Added the Neutral_till_hit flag
 *
 * 422   4/21/99 2:53p Matt
 * Added a new type for dying objects that have AI, instead of keeping a
 * flag in the dying info.
 *
 * 421   4/21/99 11:05a Kevin
 * new ps_rand and ps_srand to replace rand & srand
 *
 * 420   4/20/99 8:55p Chris
 * Fixed problem with robots not being able to open locked doors that a
 * player has the key for.
 *
 * 419   4/18/99 10:23a Chris
 *
 * 418   4/18/99 5:38a Chris
 * Drastically improved the find_random_room function and added the
 * makenextroomlist function
 *
 * 417   4/15/99 1:32a Jeff
 * linux changes to compile   /Main0 /Main1 /Main2 /Main3 /Main4 /Main5
 * /Main6 /Main7 /Main8 /Main9 /descent3/Main0 /descent3/Main1
 * /descent3/Main2 /descent3/Main3 /descent3/Main4 /descent3/Main5
 * /descent3/Main6 /descent3/Main7 /descent3/Main8 /descent3/Main9
 * AImain.cpp0 AImain.cpp1 AImain.cpp2 AImain.cpp3 AImain.cpp4 AImain.cpp5
 * AImain.cpp6 AImain.cpp7 AImain.cpp8 AImain.cpp9 linux0 linux1 linux2
 * linux3 linux4 linux5 linux6 linux7 linux8
 *
 * 416   4/14/99 10:31p Jeff
 * fixed name of ai_info struct to t_ai_info
 *
 * 415   4/14/99 2:50a Jeff
 * fixed some case mismatched #includes
 *
 * 414   4/12/99 6:15p Samir
 * Sound priorities pass 1
 *
 * 413   4/12/99 5:45p Chris
 * Improved Freud
 *
 * 412   4/10/99 6:39p Matt
 * Only save the designer-editable AI data in the Object_info array,
 * instead of the whole ai_frame structure.  This saves 3200 bytes per
 * Object_info entry, which is about 2 MB overall.
 *
 * 411   4/09/99 10:33a Chris
 * Improvements to Freud
 *
 * 410   4/08/99 7:46p Chris
 * Improving Freud
 *
 * 409   4/08/99 6:03p Chris
 * Improved Freud
 *
 * 408   4/08/99 3:35p Chris
 * Improved the Fear factor in Freud
 *
 * 407   4/07/99 3:55a Chris
 * Independant (non-parented) Rebel robots will now fire on PTMC and
 * Hostile robots.  :)
 *
 * 406   4/06/99 11:04p Chris
 * Global Unique id's for goals and circle dist stuff can be set when
 * aware barely
 *
 * 405   4/06/99 6:36p Jason
 * CHRIS -- Fixed a bug with AIDetermineFovVec()
 *
 * 404   4/06/99 11:18a Chris
 * Fixed a big bug in the attach system where object's properties where
 * not correctly reset after the attach
 *
 * 403   4/05/99 3:18p Chris
 * Patching wandering code
 *
 * 402   4/05/99 11:36a Chris
 *
 * 401   4/05/99 11:36a Chris
 * Fixed a few bugs with Orient to Node
 *
 * 400   4/02/99 3:55p Chris
 * Fixed or at least commented about guidebot bugs
 *
 * 399   4/02/99 3:49p Chris
 * Create GBs in multiplayer
 *
 * 398   4/02/99 10:18a Chris
 * We can now mess with the Object_info anim stuff
 *
 * 397   3/30/99 4:32p Chris
 * Moved subtype to the main goal sturct (from goal_info).  Made move
 * relative object vec finishable.  (Like get behind player)
 *
 * 396   3/29/99 5:32p Kevin
 * Build fixes
 *
 * 395   3/27/99 1:08p Chris
 * AIPowerSwitch now prop's though all objects that are attached to the
 * object that is turned on/off
 *
 * 394   3/26/99 6:57p Chris
 * Fixed a bug with the landing code
 *
 * 393   3/26/99 2:58p Chris
 * See sounds play 90% of the time
 *
 * 392   3/25/99 4:56p Chris
 * Added code for the land on object DALLAS goal
 *
 * 391   3/25/99 12:00p Chris
 *
 * 390   3/25/99 11:56a Jason
 * changed some sequencing bugs
 *
 * 389   3/23/99 11:51a Matt
 * Made wander code not crash if the room selected was an outside room
 * (from an inside wander)  I.e. two rooms in two different mines with
 * terrain between them.
 *
 * 388   3/22/99 7:10p Chris
 * Added path node orientation
 *
 * 387   3/22/99 3:56p Chris
 *
 * 386   3/22/99 10:58a Chris
 * Awareness code was tweaked.  Multisafe stuff added for objects.
 *
 * 385   3/18/99 12:46p Chris
 * Fixed an FOV and awareness conflict
 *
 * 384   3/17/99 5:23p Chris
 * Fixed problems with low-priority paths
 *
 * 383   3/15/99 2:39p Chris
 * Added some terrain avoidance
 *
 * 382   3/12/99 7:10p Chris
 * Avoid avoid walls version 1.0
 *
 * 381   3/12/99 12:16p Chris
 * Blending primary and blend goals!!!!!!  Awesome.
 *
 * 380   3/10/99 4:15p Chris
 * Patches birds for now
 *
 * 379   3/09/99 2:42p Chris
 * Backwards gone
 *
 * 378   3/09/99 2:13p Chris
 * Robots flying backwards
 *
 * 377   3/05/99 6:07p Chris
 * Fixed bug where OSIRIS wasn't informed at the 'level' level that a
 * goal_uid was completed (it was and still is fine at the object level)
 *
 * 376   3/05/99 10:33a Chris
 * Fixed the bashed it_handle bug
 *
 * 375   3/04/99 12:44p Chris
 * Commented out Ignore height diff code -- chrishack
 *
 * 374   3/03/99 5:35p Kevin
 * HAck
 *
 * 373   3/03/99 3:12p Chris
 * No AI firing during cinematics
 *
 * 372   3/03/99 1:18p Chris
 * Init'ed the perceived_vec_to_target
 *
 * 371   3/03/99 7:22a Chris
 * Added Napalmed to the list
 *
 * 370   3/03/99 6:52a Chris
 * Fixed headlight
 *
 * 369   3/03/99 5:47a Chris
 *
 * 368   3/03/99 5:47a Chris
 * Fixed the headlight thing
 *
 * 367   3/03/99 5:45a Chris
 * Further cased out the auto-turn stuff
 *
 * 366   3/02/99 11:41p Chris
 *
 * 365   3/02/99 10:53p Chris
 *
 * 364   3/02/99 10:46p Chris
 * Improved the vis code
 *
 * 363   3/02/99 5:39p Chris
 * Fixed the gunboy rotation problem
 *
 * 362   3/01/99 7:19p Chris
 * Fixed dist problems with finding nearby objects
 *
 * 361   2/28/99 11:30p Chris
 * FindObjOfType and OSIRIS controllable deaths
 *
 * 360   2/25/99 5:43p Chris
 * Massive improvement to BOA and AI (again)
 *
 * 359   2/25/99 10:57a Matt
 * Added new explosion system.
 *
 * 358   2/24/99 12:27p Chris
 * Fixed problems with GB finding robots/room he couldn't get to.  Fixed
 * problems with forcefields(sound prop. and path finding).  Fixed
 * problems with small portals.
 *
 * 357   2/18/99 3:50p Chris
 * Updated the exact stopping code for paths.  Scaled acceleraion by
 * max_speed scalar.
 *
 * 356   2/17/99 8:47p Chris
 * See if this fixes Dan's rotating walker problem
 *
 * 355   2/17/99 1:21a Chris
 * Updated the AI movement algorithm, fixed many bugs, added the
 * last_dodge_dir vector so that robots can dodge the vauss and the like
 *
 * 354   2/15/99 9:03p Chris
 * Added the base FOV off UVEC code and converted all the turrets
 *
 * 353   2/15/99 8:59a Chris
 *
 * 352   2/15/99 8:58a Chris
 *
 * 351   2/15/99 8:55a Chris
 * Fixed a bug with AIF_XZ_DIST (It incorrectly computed the distance from
 * a target)
 *
 * 350   2/12/99 11:19a Chris
 * If max_turn_rate is zero, then don't call the orient code
 *
 * 349   2/10/99 4:02p Chris
 * Updated the attach system so that if a robot is idling, the AI will not
 * update the attached subobjects (if the object is still moving, physics
 * will do it).
 *
 * 348   2/10/99 2:41p Chris
 * Added debug info
 *
 * 347   2/10/99 1:47p Matt
 * Changed object handle symbolic constants
 *
 * 346   2/09/99 3:52p Chris
 * Fixed melee attacks
 *
 * 345   2/09/99 12:40p Chris
 * More aipath stuff has been merged with the new BOA
 *
 * 344   2/09/99 9:58a Chris
 * Massive BOA update  :)  Terrain happy now.  Vis happy now.  Sound happy
 * now.
 *
 * 343   2/03/99 11:09a Chris
 * Stop at position goals will now get the AIN_GOAL_COMPLETE correctly
 *
 * 342   2/02/99 12:24p Sean
 * CHRIS -- Fixed a bug with dummy turrets.  They wehre using a bogus
 * index.
 *
 * 341   2/02/99 11:27a Chris
 * Added the AIN_MOVIE_START and AIN_MOVIE_END notifies
 *
 * 340   2/02/99 9:23a Chris
 * Fixed turning problems caused by zero vectors (which return a random
 * vector)
 * Fixed jitteryness problem caused by having too tight of a need-to-turn
 * tolerance on large robots
 *
 * 339   2/02/99 9:06a Chris
 * Fixed a bug where robots where starting in AS_ALERT instead of AS_IDLE
 *
 * 338   1/31/99 10:43p Chris
 * added WBF_AIM_FVEC
 *
 * 337   1/29/99 5:27p Luke
 * CHRIS - Updated the Gaurd goal
 *
 * 336   1/29/99 5:10p Chris
 * Added an optional parent handle check for FindObjOfType
 *
 * 335   1/26/99 2:51p Chris
 * AIG_WANDER improvements
 *
 * 334   1/25/99 7:43a Chris
 * Added the GUID (Goal Unique Id) and added the ability for weapon
 * batteries to always fire exactly forward.
 *
 * 333   1/24/99 10:58p Chris
 * Fixed problems with AvoidObj code
 *
 * 332   1/24/99 8:17p Chris
 * Updated AI and OSIRIS.  Externalized fireball constants for spew and
 * sparks.  Added CreateRandomSparks to OSIRIS, renamed a bunch of AI
 * Notify names to use underscores.  Fixed a memory access leak in the
 * matcen effect code.
 *
 * 331   1/23/99 2:20p Chris
 * Removed a walker hack
 *
 * 330   1/22/99 6:53p Chris
 * Fixed LoadandBind Aux notify problems, fixed static path problems,
 * fixed AIF_FORCE_AWARE Problems, improved path code
 *
 * 329   1/21/99 11:15p Jeff
 * pulled out some structs and defines from header files and moved them
 * into seperate header files so that multiplayer dlls don't require major
 * game headers, just those new headers.  Side effect is a shorter build
 * time.  Also cleaned up some header file #includes that weren't needed.
 * This affected polymodel.h, object.h, player.h, vecmat.h, room.h,
 * manage.h and multi.h
 *
 * 328   1/20/99 2:13a Chris
 * It is now possible for robots to have special immunities, resistances,
 * and vunerabilities
 *
 * 327   1/20/99 1:01a Chris
 * Improved AI and OSIRIS intergration
 *
 * 326   1/18/99 8:07p Chris
 * Added the no-collide same flag (for flocks and nests)
 *
 * 325   1/18/99 10:14a Chris
 *
 * 324   1/18/99 9:05a Chris
 * Improved OSIRIS, AI, and ATTACH system, changed wiggle code, changed
 * attach code for rad attaches, and added the AIG_ATTACH_OBJ goal
 *
 * 323   1/15/99 5:57p Chris
 * fixed some awareness bugs
 *
 * 322   1/13/99 6:37a Jeff
 * fixed object.h.  There were numerous struct declarations that were the
 * same name as the instance of the struct (gcc doesn't like this).
 * Changed the struct name.  Also added some #ifdef's for linux build,
 * along with fixing case-sensitive includes
 *
 * 321   1/13/99 2:28a Chris
 * Massive AI, OSIRIS update
 *
 * 320   1/11/99 2:14p Chris
 * Massive work on OSIRIS and AI
 *
 * 319   1/06/99 5:06p Chris
 * Improving OSIRIS/game intergration - improved support for custom
 * animations
 *
 * 318   1/05/99 6:28p Chris
 * Fix OSIRIS AI_Notify problem
 *
 * 317   12/30/98 3:46p Chris
 * Incremental AI changes
 *
 * 316   12/23/98 6:10p Matt
 * Fixed compiler warnings
 *
 * 315   12/18/98 5:40p Chris
 * Fixed a crash bug in the new OSIRIS
 *
 * 314   12/17/98 12:08p Jeff
 * first checkin of new implementation of OSIRIS (old OSIRIS no longer
 * works)
 *
 * 313   12/16/98 3:55p Chris
 * Improved the sickles
 *
 * 312   12/15/98 4:58p Chris
 * Improved the path system
 *
 * 311   12/15/98 4:08p Chris
 * Removed the annoying stop mprintf
 *
 * 310   12/15/98 4:04p Chris
 * Wall landers work
 *
 * 309   12/14/98 2:04p Chris
 * Fixed an evader1 blend problem
 *
 * 308   12/14/98 1:07p Chris
 * Allowed OSIRIS to change AI types
 *
 * 307   12/14/98 12:03a Chris
 * Turning and orientation are done in one (minus a few hacks) spot
 *
 * 306   12/13/98 9:18p Chris
 * Improved influence values for in-code goals (10000 to 1.0).  Added
 * GF_ORIENT stuff.  :)
 *
 * 305   12/12/98 10:11p Chris
 * Cleaned up some CT stuff
 *
 * 304   12/11/98 6:24p Chris
 * Additional Comments
 *
 * 303   12/11/98 1:57p Chris
 * Improved wall walking code
 *
 * 302   12/11/98 12:04p Chris
 * Improved the flocking hack.  :)
 *
 * 301   12/08/98 4:27p Chris
 * Fixed all avoid code from avoiding attached robots
 *
 * 300   12/08/98 2:14p Chris
 * Fixed bugs when an object is avoiding a robot the is attached to it
 *
 * 299   12/03/98 5:45p Chris
 * I just added full code support for OSIRIS/DLL controlled goals,
 * enablers, and influence levels.  :)
 *
 * 298   12/03/98 2:31p Chris
 * The auto-avoid friends flag is now cooler now (they avoid at greater
 * distances when they are within thier circle distance from a targetted
 * enemy)
 *
 * 297   12/03/98 12:24p Chris
 * Improved new anim code for instant updating
 *
 * 296   12/03/98 12:04p Chris
 * Further de-hacked flocking and other major AI systems
 *
 * 295   12/02/98 5:51p Chris
 * Lint cleaning
 *
 * 294   12/02/98 2:27p Chris
 * Algorithm swap stuff for target leading
 *
 * 293   12/02/98 2:13p Chris
 * We now use the target lead accuracy slider
 *
 * 292   12/01/98 6:17p Chris
 * Height bias is only for outside and GoalDetermineTrackDist is closer to
 * final
 *
 * 291   12/01/98 5:09p Chris
 * Improved the height bias code
 *
 * 290   12/01/98 4:31p Chris
 * Checked in a massive amount of AI work.  Improved flocking code.  :)
 * (Still hacked lightly).  In addition, I am moving toward using the
 * composite dir.  :)
 *
 * 289   12/01/98 3:31p Keneta
 * Added a temp fix for avoid_obj when there are no objs
 *
 * 288   11/23/98 3:11p Kevin
 * Demo system
 *
 * 287   11/23/98 11:26a Chris
 * More improvements to the AI system
 *
 * 286   11/23/98 11:09a Chris
 * Incremental improvements
 *
 * 285   11/20/98 11:37a Chris
 * Improved avoidance code
 *
 * 284   11/19/98 8:55p Chris
 *
 * 283   11/19/98 8:55p Chris
 *
 * 282   11/19/98 8:55p Chris
 * I am being to clean up the structure
 *
 * 281   11/19/98 8:26p Chris
 * Starting to add generic team avoidance code
 *
 * 280   11/18/98 6:25p Chris
 * Dodge->avoid->normal.  That is the order.  To do it right, dodge will
 * get a BIG scalar, avoid will get a smaller scalar, and normal stuff
 * will get a tiny scalar.
 *
 * 279   11/18/98 3:59p Chris
 * I added the avoid goal.  I also improved the AIs for Evader1 and
 * Evader2 by utilizing this goal when the target is well within the
 * circle distance.
 *
 * 278   11/17/98 4:16p Kevin
 * Demo recording system
 *
 * 277   11/11/98 7:18p Jeff
 * changes made so that a dedicated server's team is always -1 (team game
 * or not)
 *
 * 276   11/11/98 6:31p Chris
 * AIF_DISABLE_FIRING and AIF_DISABLE_MELEE are now functional
 *
 * 275   11/11/98 2:46p Kevin
 * Demo recording system work
 *
 * 274   11/11/98 12:11p Chris
 * The attach system and weapon firing (continous and spray) are now
 * network friendly
 *
 * 273   11/10/98 6:17p Chris
 * Improved AI - added support for manual max firing distances
 *
 * 272   11/09/98 3:08p Kevin
 * Turned off AI while playing back a demo
 *
 * 271   11/06/98 5:34p Chris
 *
 * 270   11/06/98 11:39a Chris
 * Robots with flamethrowers and Omega cannons work in single player
 *
 * 269   10/29/98 1:45p Chris
 * Checked in the better collision response code
 *
 * 268   10/28/98 4:37p Chris
 * Robots who are parented by ghosts still know their team.
 *
 * 267   10/22/98 5:36p Chris
 * Fixed ObjGet bugs
 *
 * 266   10/22/98 2:58p Chris
 * Difficulty levels are in beta
 *
 * 265   10/21/98 5:35p Chris
 * Added friend forgiving to the aggression slider
 *
 * 264   10/21/98 7:33a Chris
 * Dead objects are not-targetable
 *
 * 263   10/20/98 11:56p Chris
 *
 * 262   10/20/98 10:52p Chris
 * Improved the single player targeting when a player is dead
 * (Player->buddy->none)
 *
 * 261   10/19/98 7:20p Chris
 * Added custom fire dot code
 *
 * 260   10/19/98 7:17p Matt
 * Added system to support different types of damage to the player and
 * have these different types make different sounds.
 *
 * 259   10/16/98 3:39p Chris
 * Improved the object linking system and AI and physics
 *
 * 258   10/15/98 3:26p Chris
 * Fixed known ground plane issues and used PhysCalcGround everywhere
 *
 * 257   10/14/98 7:04p Chris
 * Update turret sound code
 *
 * 256   10/14/98 6:54p Chris
 * Added turret change direction sounds and level goal ability to toggle
 * auto level end
 *
 * 255   10/14/98 4:45p Chris
 * Added support for a endlevel in-game movie
 *
 * 254   10/14/98 3:39p Chris
 * Improved robot dodging and firing
 *
 * 253   10/13/98 1:08p Chris
 * Greatly improved the AI's use of paths.  Improved visability checking
 * algorithm.   Probably needs a second pass for further cleanup.
 *
 * 252   10/09/98 4:01p Chris
 *
 * 251   10/09/98 2:24a Chris
 *
 * 250   10/09/98 2:22a Chris
 * Improving vis checking
 *
 * 249   10/09/98 2:17a Chris
 *
 * 248   10/09/98 1:39a Chris
 * Added very infrequent target updating for robots with an awareness less
 * than AWARE_BARELY
 *
 * 247   10/09/98 1:35a Chris
 * Fixed a bug with robots only attacking after they are rendered
 *
 * 246   10/08/98 8:49p Chris
 * Improving AI initialization?
 *
 * 245   10/07/98 10:06p Chris
 * Improved the attach system's updating
 *
 * 244   10/07/98 3:37p Chris
 * Improved the melee attack code
 *
 * 243   10/07/98 12:39p Chris
 * Added support for zero latency attacks
 *
 * 242   10/07/98 10:54a Chris
 * Matcens use the birth animations
 *
 * 241   10/06/98 6:19p Chris
 * Improved OSIRIS/AI intergration
 *
 * 240   10/06/98 5:45p Kevin
 * Added new configuration for demo
 *
 * 239   9/30/98 4:40p Chris
 *
 * 238   9/30/98 4:36p Chris
 * Fixed a targetting bug
 *
 * 237   9/30/98 3:49p Chris
 * Changed comment
 *
 * 236   9/29/98 3:11p Chris
 *
 * 235   9/28/98 7:23p Chris
 * same as prev
 *
 * 234   9/28/98 7:03p Chris
 * Improved targetting of objects by AIs
 *
 * 233   9/28/98 6:23p Chris
 * Changed multi_anim to custom_anim
 *
 * 232   9/28/98 4:09p Chris
 * Added birth animations
 *
 * 231   9/28/98 1:15p Chris
 * Fixed the targetting of parents(oops) after parent-collide-timeout
 *
 * 230   9/28/98 10:34a Chris
 * Fixed a semi-colon bug
 *
 * 229   9/22/98 6:03p Samir
 * ifdef out DoAI if not in debug version.
 *
 * 228   9/17/98 11:11a Chris
 * Worked on goal system and improved integration with OSIRIS (better
 * EVT_AI_INIT event calling)
 *
 * 227   9/16/98 4:30p Chris
 * Added target by distance
 *
 * 226   9/15/98 7:29p Chris
 * Improved OSIRIS and AI intergration
 *
 * 225   9/14/98 1:14p Chris
 * Improved multiplayer team/non-team support
 *
 * 224   9/14/98 12:56p Chris
 * Automatically put player parented objects as part of AIF_TEAM_REBEL
 *
 * 223   9/14/98 12:23p Chris
 *
 * 222   9/14/98 12:16p Chris
 * Vastly improved the multiplayer code
 *
 * 221   9/11/98 5:27p Chris
 * Further improved the cooperative multiplayer ai
 *
 * 220   9/11/98 11:58a Chris
 * Fixed too many sounds in cooperative multiplayer
 *
 * 219   8/25/98 10:44a Chris
 * Worked on leading code a bit
 *
 * 218   8/25/98 10:21a Chris
 * Removed 2 annoying mprintfs
 *
 * 217   8/19/98 6:25p Chris
 * Added the infighting sliders
 *
 * 216   8/17/98 4:55p Chris
 * Reduced infighting
 *
 * 215   8/15/98 6:10p Chris
 * Added OSIRIS controlled firing
 *
 * 214   8/12/98 6:10p Chris
 * Added more to the attach code.  Added support for OBJ_DUMMY
 *
 * 213   8/10/98 12:16p Chris
 * Added AI_NumHostileAlert
 *
 * 212   8/06/98 11:49a Chris
 * OBJ_NONE objects where getting notified of stuff
 *
 * 211   8/03/98 3:59p Chris
 * Added support for FQ_IGNORE_WEAPONS, added .000001 attach code, fix a
 * bug in polymodel collision detection
 *
 * 210   7/29/98 10:24a Chris
 * Improved target updating code for multiplayer
 *
 * 209   7/28/98 5:48p Chris
 *
 * 208   7/28/98 5:41p Chris
 *
 * 207   7/28/98 5:04p Chris
 * Added some new multiplayer support (for dodging and targetting)
 *
 * 206   7/24/98 6:06p Chris
 * Initial robot leading code  -- needs multiple wb support
 *
 * 205   7/17/98 6:08p Chris
 * Greatly improved homing performance
 *
 * 204   7/14/98 5:52p Kevin
 * Packet loss measurements and auto pps adjusting
 *
 * 203   7/09/98 3:36p Chris
 *
 * 201   7/09/98 1:05p Chris
 * Added some parenthesis
 *
 * 200   7/09/98 12:44p Chris
 *
 * 199   7/09/98 12:34p Chris
 * Fixed a problem with the current interp code
 *
 * 198   7/09/98 12:31p Chris
 * Improved the turret interp code
 *
 * 197   7/09/98 11:34a Chris
 * Turrets are interpolated.
 *
 * 196   7/08/98 1:02p Chris
 *
 * 195   7/08/98 12:11p Chris
 *
 * 194   7/08/98 11:38a Chris
 * Improved the turret info passing in multiplayer
 *
 * 193   7/07/98 11:29a Chris
 *
 * 192   7/07/98 10:10a Kevin
 * Added basic turret support for coop
 *
 * 191   7/06/98 10:27a Chris
 * Re-added general awareness
 *
 * 190   7/02/98 6:08p Chris
 * Removed the quick hack way of doing awareness
 *
 * 189   7/01/98 7:11p Chris
 * Added multi blocks
 *
 * 188   7/01/98 6:36p Chris
 * Added more multiplayer support
 *
 * 187   7/01/98 4:35p Chris
 * More multiplayer sync issues
 *
 * 186   7/01/98 2:02p Chris
 * Added the sound for animations
 *
 * 185   7/01/98 10:58a Chris
 * Working on multiplayer AI stuff
 *
 * 184   6/30/98 6:36p Chris
 * Added rev .1 of multiplayer animations - BTW  It is totally not done.
 *
 * 183   6/29/98 1:50p Chris
 * Fixed a turning multiplayer bug
 *
 * 182   6/29/98 1:35p Chris
 * Incremental improvements
 *
 * 181   6/29/98 1:12p Chris
 * Dodge updates
 *
 * 180   6/29/98 12:34p Chris
 * Fighting robots get some notification of hostile fire
 *
 * 179   6/29/98 10:20a Chris
 * Someone changed the way ObjGet works.
 *
 * 178   6/26/98 4:57p Chris
 * Less flinching
 *
 * 177   6/26/98 4:03p Chris
 * Added support for AI's changing targets -- VERY NOT DONE
 *
 * 176   6/26/98 2:52p Chris
 * AI now reports when it updates its orientation
 *
 * 175   6/25/98 3:40p Chris
 * Made AINotify work correctly (i.e. not at all) on clients
 *
 * 174   6/25/98 11:02a Chris
 * Made clients bail.
 *
 * 173   6/15/98 6:29p Chris
 * Added FQ_NO_RELINK to the homing code
 *
 * 172   6/15/98 5:45p Chris
 *
 * 171   6/15/98 5:18p Chris
 * Added version 1 of the multiple ground point code
 *
 * 170   6/15/98 3:23p Chris
 * Single point walker update
 *
 * 169   6/03/98 6:42p Chris
 * Added multipoint collision detection an Assert on invalid (infinite
 * endpoint).
 *
 * 168   6/01/98 9:24p Chris
 * Improved the code for AIs that are off
 *
 * 167   5/27/98 5:54p Chris
 * If AI is off, no notifies are received
 *
 * 166   5/27/98 3:19p Chris
 * Made disabled AIs ignore dodge notifications
 *
 * 165   5/26/98 7:57p Chris
 * Worked on the avoid hack
 *
 * 164   5/26/98 7:41p Chris
 * Made hoppers not converge
 *
 * 163   5/26/98 5:04p Chris
 * rev .2 of walking
 *
 * 162   5/26/98 4:39p Chris
 * rev. .1 of walker code
 *
 * 161   5/26/98 4:10p Chris
 * Removed a hack
 *
 * 160   5/26/98 2:49p Chris
 * More fixes
 *
 * 159   5/26/98 2:26p Chris
 * Fixed the circle distance bug in AIGoalMoveRelativeObjectVec
 *
 * 158   5/26/98 10:03a Chris
 * move relative object and orient to vel where causing problems with each
 * other.   I found a temp solution
 *
 * 157   5/26/98 9:45a Chris
 * DIstance and vec_to_target are independant
 *
 * 156   5/26/98 9:34a Chris
 * Added XZ distances for circle dist.  :)
 *
 * 155   5/22/98 6:50p Chris
 * Improving the melee attacks
 *
 * 154   5/22/98 6:45p Chris
 * Fixed a bug with flinching and melee attacks
 *
 * 153   5/22/98 6:28p Chris
 * Working on melee attacks
 *
 * 152   5/22/98 6:22p Chris
 * Improved Dynamic path allocation
 *
 * 151   5/22/98 4:44p Chris
 * Added better melee hit prediction
 *
 * 150   5/22/98 11:59a Chris
 * Fixed improper uses of FindSoundName and made the proper static sounds
 *
 * 149   5/20/98 5:12p Chris
 * Print the notify number a robot gets when it is invalid
 *
 * 148   5/20/98 10:22a Chris
 * Improved targetting stuff
 *
 * 147   5/20/98 10:19a Chris
 * Fixed some bugs with status_reg's and circle distance
 *
 * 146   5/19/98 2:53p Chris
 * CreateObject in OSIRIS works outside now.
 *
 * 145   5/18/98 8:06p Chris
 * Made melee attacks closer to what I want in terms of functionality
 *
 * 144   5/18/98 12:40p Chris
 * Added a new flag (F_BLINE_IF_SEE_GOAL)
 *
 * 143   5/18/98 11:16a Chris
 * Fixed a problem with the GetToObj goal (an if statement was f*cked up)
 *
 * 142   5/17/98 9:07p Chris
 * Fixed melee attacks.  Thanks to Ala.  :)
 *
 * 141   5/17/98 8:05p Chris
 *
 * 140   5/17/98 7:54p Chris
 * Correctly integrated the goal system and circle distance stuff.  Added
 * support for "target goals".
 *
 * 139   5/15/98 2:58p Chris
 * More on the big AI update
 *
 * 138   5/14/98 3:01p Chris
 * More new AI code
 *
 * 137   5/14/98 12:21p Chris
 * Updating AI system... Incomplete
 *
 * 136   5/12/98 3:46p Chris
 * Added some notify/goal system stuff and orientation to velocity
 *
 * 135   5/11/98 4:39p Chris
 * Improved AI system (goals have notifies and are more flexable).
 *
 * 134   5/04/98 4:20p Chris
 * Energy Drain
 *
 * 133   5/04/98 4:04p Chris
 * Minestone checkin' -- energy effect and more AI functionality
 *
 * 132   5/04/98 12:22p Chris
 * Hacked some buddy bot code
 *
 * 131   5/04/98 11:00a Chris
 * Hacks
 *
 * 130   5/03/98 7:02p Chris
 * Improved sound support for AI system
 *
 * 129   5/03/98 6:03p Chris
 * Added sound support to the animation system
 *
 * 128   5/03/98 5:38p Chris
 * Added sounds to anim page
 *
 * 127   5/01/98 7:53p Chris
 *
 * 126   5/01/98 7:52p Chris
 * Turn toward player - not last see position
 *
 * 125   5/01/98 3:41p Chris
 *
 * 124   5/31/98 3:03p Chris
 * Added death animations
 *
 * 123   4/30/98 2:03p Chris
 * Fixed the robot jiggyness problem.  :)
 *
 * 122   4/30/98 11:31a Chris
 * Massive upgrades to the AI system
 *
 * 121   4/22/98 9:43p Chris
 * More AI improvements
 *
 * 120   4/22/98 4:15p Chris
 * Improved DebugBlockPrint
 *
 * 119   4/22/98 3:50p Chris
 * Added DebugBlockPrint
 *
 * 118   4/22/98 1:15p Chris
 * Incremental work on paths and goals
 *
 * 117   4/21/98 11:25a Chris
 * Improving GET_TO_OBJ goal
 *
 * 116   4/20/98 12:27p Chris
 * Made AIG_GET_TO_OBJECT work.
 *
 * 115   4/19/98 9:56p Chris
 * AI system is integrated with OSIRIS.  Path system is integrated with
 * the AI system.  Bugs will ensue.
 *
 * 114   4/17/98 1:59p Jason
 * added cool object effects
 *
 * 113   4/16/98 2:56p Chris
 * Updated buddy support and intergrated scripting and AI
 *
 * 112   4/15/98 5:56p Chris
 * Made the AI system script friendly
 *
 * 111   4/14/98 3:20p Chris
 * Made quirks happen more often
 *
 * 110   4/14/98 11:42a Chris
 * Added quirks and a better way of getting from idle to alert and from
 * alert to idle.
 *
 * 109   4/13/98 7:38p Chris
 * Added more support for a 'real' AI.
 *
 * 108   4/13/98 6:54p Chris
 * Improved the animation system.
 *
 * 107   4/13/98 2:20p Chris
 * IDLe works (kindof)
 *
 * 106   4/07/98 4:25p Chris
 * Added support for buddy bot
 *
 * 105   3/31/98 4:23p Chris
 * Added a new AIpath system
 *
 * 104   3/25/98 5:51p Chris
 * Added full model/body animations for weapon firing
 *
 * 103   3/25/98 11:02a Chris
 * version 1.0 of the new AI ranged firing code.
 *
 * 102   3/24/98 3:20p Chris
 * Improved local wb anim system
 *
 * 101   3/23/98 6:16p Chris
 * added some soar_helpers and some debug mprintf's
 *
 * 100   3/23/98 10:01a Chris
 * Added independant wb animations
 *
 * 99    3/17/98 11:27a Chris
 * Added object bump notifies for AI
 *
 * 98    3/13/98 5:55p Chris
 * Fixed problems with animations
 *
 * 97    3/12/98 7:30p Chris
 * Added ObjSetOrient
 *
 * 96    3/12/98 5:48p Chris
 * Fixed a bug in the animation cycle times
 *
 * 95    3/10/98 2:15p Chris
 * Made turrets with a zero angle fov usable to join sub-objects (for fire
 * animations)
 *
 * 94    3/10/98 12:51p Chris
 * Added a truely D2 style homing missile
 *
 * 93    3/05/98 11:34a Chris
 * Added the move_behind_object function
 *
 * 92    3/03/98 5:02p Chris
 * Added a status register to the ai_frame.  Also, I enabled a bunch of
 * the fields from the AI Dialog.  In addiition, I tweaked how melee
 * attacks work and animate.
 *
 * 91    3/02/98 6:52p Chris
 * Changed melee_dist to melee_damage
 *
 * 90    2/27/98 7:22p Chris
 * Started to add new AI fields -- no way near complete
 *
 * 89    2/20/98 3:24p Chris
 *
 * 88    2/19/98 6:16p Chris
 * Working on AI
 *
 * 87    2/18/98 8:42p Chris
 * Improving on the big object problem
 *
 * 86    2/18/98 4:47a Chris
 *
 * 85    2/18/98 4:38a Chris
 *
 * 84    2/18/98 4:37a Chris
 *
 * 83    2/18/98 4:18a Chris
 *
 * 82    2/18/98 4:13a Chris
 *
 * 81    2/18/98 4:05a Chris
 *
 * 80    2/17/98 11:31p Chris
 *
 * 79    2/17/98 4:24p Chris
 * Allow for simple walking robots
 *
 * 78    2/17/98 1:34p Chris
 * Improved timing of tear sound for melee
 *
 * 77    2/17/98 1:17p Chris
 * Improving the melee robots
 *
 * 76    2/17/98 1:05p Chris
 * Added in melee hit sound and effect
 *
 * 75    2/16/98 11:19p Chris
 * Added support for melee robots
 *
 * 74    2/16/98 4:56p Chris
 * Added melee attack support
 *
 * 73    2/16/98 3:50p Chris
 * Robots take melee swipes
 *
 * 72    2/16/98 1:05p Chris
 * Added some Flinch support
 *
 * 71    2/16/98 2:45a Chris
 * Massive improvements to the animation system and the AI
 *
 * 70    2/11/98 11:39a Chris
 *
 * 69    2/11/98 11:38a Chris
 * Added additional support to the beginning points on paths
 *
 * 68    2/11/98 11:06a Chris
 * Fixed the orient to node code.  Thanks be to AI.
 *
 * 67    2/10/98 5:48p Chris
 * Improving the heuristic for when we update_next_path nodes.
 *
 * 66    2/10/98 4:45p Chris
 * Incremental changes:  Made a new node_orient heuristic.  Removed some
 * bad fields from the ai_info struct.
 *
 * 65    2/10/98 12:09a Chris
 * Improving the awareness system.  Re-enabled super dodging.  Added the
 * auto-fluctuate speed flag (allows some diversity).  Enabled FOV
 * information.
 *
 * 64    2/06/98 5:51p Chris
 * Added the ability turn robots on and off
 *
 * 63    2/06/98 4:19p Chris
 * Added a boat load of path stuff
 *
 * 62    2/06/98 2:15a Chris
 * Activated the max_velocity, max_delta_velocity, and max_turn_rate
 * fields for AI objects.
 *
 * 61    2/05/98 6:55p Chris
 * Align orientation to path
 *
 * 60    2/04/98 6:09p Matt
 * Changed object room number to indicate a terrain cell via a flag.  Got
 * rid of the object flag which used to indicate terrain.
 *
 * 59    2/03/98 6:33p Chris
 * Improving the path system
 *
 * 58    2/03/98 3:35p Chris
 * Added path support for AI and OSIRIS
 *
 * 57    2/02/98 8:15p Chris
 * Updated the AI system
 *
 * 56    2/02/98 11:06a Chris
 *
 * 55    1/30/98 4:09p Chris
 *
 * 54    1/30/98 4:07p Chris
 *
 * 53    1/30/98 3:42p Chris
 * Removed a bad memset (it zerod out static values)
 *
 * 52    1/30/98 2:19p Chris
 * More improvements (target vis stuff and setting of the AIN_ALWAYS_ON is
 * now done correctly)
 *
 * 51    1/29/98 3:29p Chris
 * Major update to the AI system.
 *
 * 50    1/21/98 3:54p Chris
 *
 * 49    1/20/98 4:40p Chris
 * Fixed some visability stuff.
 *
 * 48    1/20/98 12:21p Chris
 * Removed some printf's
 *
 * 47    1/20/98 11:34a Chris
 * Fixed problems with player visability and thus problems with awareness
 *
 * 46    1/19/98 10:04a Matt
 * Added new object handle system
 *
 * 45    1/14/98 7:58p Chris
 *
 * 44    12/09/97 2:48p Chris
 * Temporary less dodgy bots
 *
 * 43    11/24/97 4:12p Chris
 * Cleaner code
 *
 * 42    11/24/97 10:17a Chris
 * Handles dead, dying, and cloaked players
 *
 * 41    11/21/97 3:05p Chris
 * Robots will not fired at the player after he is dead.
 *
 * 40    11/21/97 1:14p Chris
 * Improved hueristic for robot firing.
 *
 * 39    11/17/97 9:48p Chris
 * Added some guarding
 *
 * 38    11/17/97 6:01p Chris
 * thief update
 *
 * 37    11/17/97 5:59p Chris
 * Allowed some thief stuff
 *
 * 36    11/17/97 5:46p Chris
 * Added some support for a Theif-like robot
 *
 * 35    11/15/97 6:39p Chris
 * Made robot firing signifantly less CPU costly.  But, turrets are now
 * more choppy moving.
 *
 * 34    11/14/97 11:55p Chris
 * Dodge goals are semi-functional
 *
 * 33    11/13/97 3:56p Chris
 * Evading a little more random
 *
 * 32    11/13/97 3:34p Chris
 * Improved AI
 *
 * 31    11/12/97 5:47p Chris
 * Incremental improvements
 *
 * 30    11/12/97 10:43a Chris
 * Incremental
 *
 * 29    11/11/97 12:22p Chris
 * Incremental improvements
 *
 * 28    11/06/97 12:47p Chris
 * Some new incremental stuff
 *
 * 27    11/04/97 6:20p Chris
 * Added some incremental improvements
 *
 * 26    10/28/97 12:25p Chris
 * Added support for initial class, type, and movement types.  Starting to
 * flush out the AI structure
 *
 * 25    9/23/97 5:47p Jason
 * return if "animation system not done" message is printed
 *
 * 24    9/18/97 1:27p Matt
 * Cleaned up object struct
 *
 * 23    9/17/97 11:31a Chris
 *
 * 22    9/15/97 4:07p Chris
 * AI only fires if you are in the same render as they are.
 *
 * 21    9/10/97 1:24p Chris
 * Fixed a bug with the wb firing masks
 *
 * 20    9/10/97 12:56p Chris
 * Added more support for weapon batteries
 *
 * 19    9/08/97 11:50a Chris
 * Added support for entering seconds-per-cycle animation information
 *
 * 18    9/05/97 8:52p Chris
 * Furthered the weapon bank support
 *
 * 17    9/04/97 3:50p Chris
 * Added new turret support
 *
 * 16    9/03/97 2:12p Chris
 * Added new weapon battery system and made the animation system usable.
 *
 * 15    8/20/97 3:13p Chris
 *
 * 14    8/11/97 1:53p Matt
 * Ripped out robot & powerup pages, and added generic page
 *
 * 13    8/06/97 1:35p Matt
 * Changes for new generic object_info struct which replace robot-specific
 * structure
 *
 * 12    8/05/97 12:29p Chris
 *
 * 11    7/30/97 4:10p Chris
 * Made test bot more interesting.
 *
 * 10    7/30/97 1:31p Chris
 * Made helicopters slightly more interesting.
 *
 * 9     7/29/97 12:20p Chris
 * Incremental improvements.  Fixed a memory bug.
 *
 * 8     7/28/97 1:19p Chris
 * Expanding the AI system
 *
 * 7     7/16/97 5:15p Chris
 * Fixed use of updating 3d sounds
 *
 * 6     7/15/97 7:29p Chris
 * Added a sound for helicopter blades.
 *
 * 5     7/15/97 5:35p Chris
 * New AI code
 *
 * 4     7/15/97 4:59p Chris
 * added support for AI and animations
 *
 * $NoKeywords: $
 */

#include <stdlib.h>
#include "AIMain.h"
#include "mono.h"
#include "game.h"
#include "weapon.h"
#include "findintersection.h"
#include "vecmat.h"
#include "AIGoal.h"
#include "terrain.h"
#include "hlsoundlib.h"
#include "sounds.h"
#include "aiterrain.h"
#include "weapon.h"
#include "objinfo.h"
#include "polymodel.h"
#include "robotfire.h"
#include "BOA.h"
#include "player.h"
#include "memory.h"
#include "gamepath.h"
#include "soundload.h"
#include "damage.h"
#include "aipath.h"
#include "robot.h"
#include "attach.h"
#include "demofile.h"
#include "matcen.h"
#include "PHYSICS.H"
#include "difficulty.h"
#include "osiris_dll.h"
#include "multi.h"
#include "gamecinematics.h"
#include "room.h"
#include "psrand.h"
#include "gametexture.h"
#include "difficulty.h"

// Define's
#define MAX_SEE_TARGET_DIST 500.0f
#define MAX_TRACK_TARGET_DIST 800.0f
#define MIN_VIS_RECENT_CHECK_INTERVAL 0.35f
#define MIN_VIS_CHECK_INTERVAL 0.15f
#define CHECK_VIS_INFREQUENTLY_TIME 7.0f
#define CHECK_VIS_INFREQUENTLY_INTERVAL 2.0f

#define MIN_TARGET_UPDATE_INTERVAL 2.0f
#define MAX_TARGET_UPDATE_INTERVAL 4.5f

float AI_last_time_room_noise_alert_time[MAX_ROOMS + 8];
int AI_unique_goal_id = 0;

#ifdef _DEBUG
bool AI_debug_robot_do = false;
int AI_debug_robot_index = -2;
#endif

static bool compute_dodge_dir(/* vector *dodge_dir, */ object *obj, object *dodge_obj);
static float AIDetermineObjVisLevel(object *obj, object *target);
static bool move_relative_object_vec(object *obj, vector *vec, object *target, float circle_dist, float scalar,
                                     bool f_toward, vector *mdir, bool *f_moved);
static void move_away_from_position(object *obj, vector *pos /*, bool random_evade*/, float scale, vector *mdir,
                                    bool *f_moved);
static bool goal_do_dodge(object *obj, int goal_index);
static bool goal_do_avoid_walls(object *obj, vector *mdir);
static bool MeleeHitOk(object *obj);
static bool AiMelee(object *obj);
static void do_ranged_attack(object *obj);
static bool AIDetermineAimPoint(object *robot, object *target, vector *aim_pt, float weapon_speed = 0.0f);
static vector *AIDetermineFovVec(object *obj, vector *fov);
static void AISeeTarget(object *obj, bool f_see);
static void ai_do_animation(object *obj, float anim_time);
static void ObjSetAIInfo(object *objp);
static void AICheckTargetVis(object *obj);
static void ai_update_registers(object *obj);
static bool AiGoalAvoid(vector *adir, object *obj, object *a_obj, float dist);
static void AIGoalDoRepulse(object *obj, float dist, vector *dir, goal *goal, vector *mdir);
static void AIGoalDoCohesion(object *obj, object *g_obj, float dist, goal *goal, vector *mdir);
static void AIGoalDoAlignment(object *obj, float dist, vector *fvec, goal *goal, vector *mdir);
static void AIDoTrackFrame(object *obj);
static void AIDoOrientVelocity(object *obj);
static void AIDoOrientDefault(object *obj);
static void AIDoOrient(object *obj, int g_index);
static void AIDetermineSpeed(object *obj, int flags, float *speed);
static void ai_move(object *obj);
static void ai_fire(object *obj);
static int AIGetTeam(object *obj);
static void AITargetCheck(object *obj, object *target, object **best_obj, float *best_dot, float *best_dist);
static void AIDetermineTarget(object *obj);
static void AIDoFreud(object *obj);
static void AIDoMemFrame(object *obj);

// chrishack -- AI problems

// first frame problems:
// If a robot has an initial velocity it might fly off because of excessive Frametime of the first frame
// If a player fires on the first frame, robots will not know

// Inside walkers will suck resources

const char *const Ai_class_strings[MAX_AI_INIT_CLASSES] = {"Static", "Pure Path", "Fully AIS"};

const char *const Ai_type_strings[MAX_AI_INIT_TYPES] = {
    "Fly Lander", "Stalker", "Evader 1", "Evader 2", "Stationary Turret", "AIS", "Melee1", "Bird Flock 1", "Herd 1"};

const char *const Ai_movement_type_strings[MAX_AI_INIT_MOVEMENT_TYPES] = {"Standing", "Flying", "Rolling", "Walking"};

// AI Movement flying types
const char *const Ai_movement_subtype_flying_strings[MAX_AI_INIT_MOVEMENT_SUBTYPES] = {
    "Normal", "Path", "Helicopter", "Hovercraft", "Jet", "Player", "Buddy"};

// AI Movement walking types

const char *const Ai_movement_subtype_walking_strings[MAX_AI_INIT_MOVEMENT_SUBTYPES] = {
    "Restricted Flat", "Restricted Low-angle", "Restricted High_angle", "Non-restricted", "Water Only", "", ""};

#define AI_MAX_MELEE_RANGE 5.0f

int AI_NumRendered;
std::array<int, MAX_OBJECTS> AI_RenderedList;

int AI_NumHostileAlert = 0;

int Buddy_handle[MAX_PLAYERS];

static int AI_FriendNumNear = 0; // Number of friends found
static object *AI_FriendObj[2];  // Friend objects
static float AI_FriendDist[2];   // Distances to the friends
static vector AI_FriendDir[2];   // Direction to the friends
static int AI_EnemyNumNear = 0;  // Number of enemies found
static object *AI_EnemyObj[2];   // Enemy objects
static float AI_EnemyDist[2];    // Distances to the enemies
static vector AI_EnemyDir[2];    // Direction to the enemies

#define AIVIS_NONE 0.0f
#define AIVIS_BARELY 1.0f
#define AIVIS_MOSTLY 2.0f
#define AIVIS_FULL 3.0f

// Allows the vis sliders to work
float AIDetermineObjVisLevel(object *obj, object *target) {
  float vis_level = AIVIS_FULL;

  if (target == NULL)
    return AIVIS_NONE;

  if ((target->effect_info) && (target->effect_info->type_flags & EF_CLOAKED)) {
    vis_level = AIVIS_NONE;

    if (target->type == OBJ_PLAYER && (Players[target->id].flags & PLAYER_FLAGS_AFTERBURN_ON)) {
      vis_level += 1.0f;
    }

    if (target->type == OBJ_PLAYER && (Players[target->id].flags & PLAYER_FLAGS_HEADLIGHT)) {
      vector from_target = obj->pos - target->pos;
      vm_NormalizeVector(&from_target);

      if ((target->orient.fvec) * (from_target) > 0.965f) {
        vis_level += 1.0f;
      }
    }
  }

  if ((target->effect_info) && (target->effect_info->type_flags & EF_NAPALMED)) {
    vis_level += 1.75;
  }

  if (vis_level < AIVIS_NONE)
    vis_level = AIVIS_NONE;
  else if (vis_level > AIVIS_FULL)
    vis_level = AIVIS_FULL;

  return vis_level;
}

static inline bool ai_target_valid(object *obj) {
  ai_frame *ai_info = obj->ai_info;
  bool f_valid = false;

  if (ai_info->target_handle != OBJECT_HANDLE_NONE) {
    if (ObjGet(ai_info->target_handle))
      f_valid = true;
    else {
      AINotify(obj, AIN_TARGET_DIED, (void *)&ai_info->target_handle);
      ai_info->target_handle = OBJECT_HANDLE_NONE;
    }
  }

  return f_valid;
}

bool AISetTarget(object *obj, int handle) {
  ai_frame *ai_info = obj->ai_info;

  ai_info->target_handle = handle;
  if (handle == OBJECT_HANDLE_NONE)
    ai_info->last_see_target_pos = obj->pos;

  return ai_target_valid(obj);
}

// Note ASSUMES that dir is normalized
void AIMoveTowardsDir(object *obj, vector *dir, float scale) {
  physics_info *phys_info = &obj->mtype.phys_info;
  vector goal_velocity;
  vector vel_diff;
  float delta_vel;
  float max_delta_vel;
  ai_frame *ai_info = obj->ai_info;
  float acc_scale;

  if (scale < 1.0f)
    acc_scale = 1.0f;
  else
    acc_scale = scale;

  goal_velocity = *dir * ai_info->max_velocity * scale;

  vel_diff = goal_velocity - phys_info->velocity;
  delta_vel = vm_NormalizeVector(&vel_diff);

  max_delta_vel = Frametime * ai_info->max_delta_velocity * acc_scale;

  if (delta_vel > max_delta_vel) {
    phys_info->velocity += (vel_diff * max_delta_vel);
  } else {
    phys_info->velocity = goal_velocity;
  }
}

bool AIMoveTowardsPosition(object *obj, /*velocity *new_vel,*/ vector *pos, float scale, bool stop_at_end_point,
                           vector *mdir, bool *f_moved) {
  vector dir;
  float distance;
  ai_frame *ai_info = obj->ai_info;
  float acc_scale;

  if (scale < 1.0f)
    acc_scale = 1.0f;
  else
    acc_scale = scale;

  if (stop_at_end_point) {
    if (vm_VectorDistance(pos, &obj->pos) <= .2f) {
      obj->mtype.phys_info.velocity = Zero_vector;
      *f_moved = true;
      return true;
    }

    float s_to_stop = (ai_info->max_velocity * scale) / (ai_info->max_delta_velocity * acc_scale);
    float d_to_stop = ai_info->max_velocity * scale * s_to_stop;

    dir = *pos - obj->pos;
    float d_to_target = vm_NormalizeVector(&dir);
    if (d_to_target < d_to_stop) {
      float speed = ai_info->max_velocity * scale * (d_to_target / d_to_stop);

      if (d_to_target <= speed * Frametime) {
        obj->mtype.phys_info.velocity = ((d_to_target / Frametime) + .09f) * dir;
      } else {
        obj->mtype.phys_info.velocity = dir * (speed + .1f);
      }

      *f_moved = true;
      return false;
    }
  }

  if (*pos == obj->pos) {
    physics_info *phys_info = &obj->mtype.phys_info;

    if (phys_info->velocity != Zero_vector) {
      vector vel_diff = -phys_info->velocity;
      float delta_vel = vm_NormalizeVector(&vel_diff);
      float max_delta_vel = Frametime * ai_info->max_delta_velocity * acc_scale;

      if (delta_vel > max_delta_vel) {
        phys_info->velocity += (vel_diff * max_delta_vel);
      } else {
        vm_MakeZero(&phys_info->velocity);
      }
    }

    *f_moved = true;
    return false;
  } else {
    dir = *pos - obj->pos;
    distance = vm_NormalizeVector(&dir);
  }

  *mdir = dir;
  *f_moved = false;

  //	AIMoveTowardsDir(obj, &dir);
  return false;
}

bool move_relative_object_vec(object *obj, vector *vec, object *target, float circle_dist, float scalar, bool f_toward,
                              vector *mdir, bool *f_moved) {
  // Getting behind an object is a 2 step process:  Get to the side and then get behind.
  vector from_target;
  vector opposite_fvec;
  vector goal_pos;
  ai_frame *ai_info = obj->ai_info;
  bool f_done = false;

  from_target = obj->pos - target->pos;

  if (f_toward) {
    opposite_fvec = -(*vec);
  } else {
    opposite_fvec = *vec;
  }

  if (from_target * opposite_fvec > 0.0f) {
    // I am currently on the side of the object that I do not want to be on
    vector goal_dir;
    vector vec_to_plane;
    vector normal_component;
    vector plane_component;

    vec_to_plane = obj->pos - target->pos;
    normal_component = opposite_fvec * (opposite_fvec * vec_to_plane);
    plane_component = vec_to_plane - normal_component;

    if (plane_component == Zero_vector) {
      goal_dir = target->orient.rvec;
    } else {
      goal_dir = plane_component;
      vm_NormalizeVector(&goal_dir);
    }

    goal_pos = target->pos + goal_dir * (obj->size + target->size + circle_dist);
  } else {
    // else, I am going to get behind/in-front the object
    goal_pos = target->pos - (opposite_fvec * (obj->size + target->size + circle_dist));
    if (vm_VectorDistance(&goal_pos, &obj->pos) < obj->size) {
      f_done = true;
    }
  }

  AIMoveTowardsPosition(obj, &goal_pos, scalar, false, mdir, f_moved);
  return f_done;
}

void move_away_from_position(object *obj, vector *pos /*, bool random_evade*/, float scale, vector *mdir,
                             bool *f_moved) {
  vector dir;
  float distance;

  // Reverse of move towards
  dir = obj->pos - *pos;
  distance = vm_NormalizeVector(&dir);

  //	AIMoveTowardsDir(obj, &dir, scale);
  *mdir = dir;
  *f_moved = false;
}

#define NO_DODGE_SIZE_MULTIPLIER 2.0f
#define MIN_DODGE_DIST 5.0f

#define MAX_DODGE_INFLUENCE 10.0f
#define MIN_DODGE_INFLUENCE 2.5f // Just less than max avoiding fiends

// returns false if no dodge is necessary
bool compute_dodge_dir(vector *movement_dir, object *obj, object *dodge_obj) {
  vector vec_to_obj = obj->pos - dodge_obj->pos;
  vector dodge_vec;
  vector dobj_motion = dodge_obj->mtype.phys_info.velocity;
  vm_NormalizeVector(&dobj_motion);

  float closest_dist;

  float p;

  float max_dodge_dist = obj->size * NO_DODGE_SIZE_MULTIPLIER + dodge_obj->size;
  if (max_dodge_dist < MIN_DODGE_DIST) {
    max_dodge_dist = MIN_DODGE_DIST;
  }

  if (IS_GUIDEBOT(obj)) {
    max_dodge_dist += 10.0f;
  }

  vector dpoint;

  p = dobj_motion * vec_to_obj;

  if (p <= 0.0)
    return false;

  dpoint = dodge_obj->pos + (p * dobj_motion);

  dodge_vec = obj->pos - dpoint;
  closest_dist = vm_NormalizeVector(&dodge_vec);

  if (closest_dist > max_dodge_dist)
    return false;
  if (closest_dist == 0.0)
    dodge_vec = obj->orient.rvec;

  // CHRISHACK -- Use the MIN/MAX INFLUENCE and INFLUENCE RAMP
  float scale = MAX_DODGE_INFLUENCE * ((max_dodge_dist - closest_dist) / max_dodge_dist);
  if (scale < MIN_DODGE_INFLUENCE) {
    scale = MIN_DODGE_INFLUENCE;
  }

  if (IS_GUIDEBOT(obj)) {
    scale *= 20.0f;
  }

  dodge_vec *= scale;

  if (dodge_vec != Zero_vector && (obj->ai_info->dodge_till_time < Gametime ||
                                   vm_GetMagnitude(&dodge_vec) > vm_GetMagnitude(&obj->ai_info->last_dodge_dir))) {
    obj->ai_info->last_dodge_dir = dodge_vec;
  }

  obj->ai_info->dodge_till_time =
      Gametime + ((float)ps_rand() / (float)D3_RAND_MAX) * (3.0f * obj->ai_info->life_preservation) + 1.0f;

  *movement_dir += dodge_vec;

  return true;
}

bool goal_do_dodge(object *obj, int goal_index) {
  ai_frame *ai_info = obj->ai_info;
  object *other_obj = ObjGet(ai_info->goals[goal_index].g_info.handle);
  int reason = AIN_GOAL_COMPLETE;

  if (other_obj) {
    if (compute_dodge_dir(&ai_info->movement_dir, obj, other_obj)) {
      return true;
    }
  } else {
    reason = AIN_GOAL_INVALID;
  }

  GoalClearGoal(obj, &ai_info->goals[goal_index], reason);
  return false;
}

#define MAX_WALL_AVOID_INFLUENCE 0.9f
#define MAX_TERRAIN_AVOID_INFLUENCE 0.9f
#define GB_WALL_PULSE_INTERVAL 7

bool goal_do_avoid_walls(object *obj, vector *mdir) {
  fvi_face_room_list facelist[200];
  int num_faces;
  float rad;
  int i;
  vector awall_dir = Zero_vector;
  float closest_dist;
  vector pos;
  bool f_danger = false;

  float wall_size = Poly_models[obj->rtype.pobj_info.model_num].wall_size;

  if (IS_GUIDEBOT(obj)) {
    rad = 10.0f;
  } else {
    if (wall_size < 7.0f)
      rad = wall_size + 2.2f;
    else
      rad = wall_size + 1.0f;
  }

  pos = obj->pos + obj->wall_sphere_offset;

  closest_dist = rad + 1.0f;

  if (obj->mtype.phys_info.velocity == Zero_vector) {
    return false;
  }

  if (!ROOMNUM_OUTSIDE(obj->roomnum)) {
    num_faces = fvi_QuickDistFaceList(obj->roomnum, &pos, rad, facelist, 200);

    for (i = 0; i < num_faces; i++) {
      room *rp = &Rooms[facelist[i].room_index];
      face *fp = &rp->faces[facelist[i].face_index];

      int face_info = GetFacePhysicsFlags(rp, fp);
      if (!(face_info & FPF_SOLID))
        continue;

      vector fpnt = rp->verts[fp->face_verts[0]];

      // Ignore backfaces
      if ((pos - fpnt) * fp->normal > 0.0f) {
        float dist = vm_DistToPlane(&pos, &fp->normal, &fpnt);

        if (dist < rad) {
          vector pnt_on_face = pos - (dist * fp->normal);
          vector *vertex_ptr_list[MAX_VERTS_PER_FACE];
          int j;

          for (j = 0; j < fp->num_verts; j++) {
            vertex_ptr_list[j] = &rp->verts[fp->face_verts[j]];
          }

          int edgemask = check_point_to_face(&pnt_on_face, &fp->normal, fp->num_verts, vertex_ptr_list);

          if (edgemask == 0) {
            float scale = 1.0f - ((dist - wall_size * .5f) / (rad - wall_size * .5f));
            if (scale < 0.0)
              scale = 0.0f;
            else if (scale > 1.0f)
              scale = 1.0f;

            awall_dir += (scale * fp->normal);

            //						mprintf(0, "%d\n", facelist[i].face_index);
            if (GameTextures[fp->tmap].flags & (TF_VOLATILE | TF_FORCEFIELD | TF_LAVA)) {
              if (!(fp->portal_num >= 0 && !(rp->portals[fp->portal_num].flags & PF_RENDER_FACES))) {
                f_danger = true;
              }
            }

            // mprintf(0, "Dist %f %f (%d, %d)\n", dist, scale, facelist[i].room_index, facelist[i].face_index));

            if (dist < closest_dist) {
              closest_dist = dist;
            }
          }
        }
      }
    }
  } else {
    int num_cells;
    int cell_list[100];

    num_cells = fvi_QuickDistCellList(CELLNUM(obj->roomnum), &pos, rad, cell_list, 100);

    for (i = 0; i < num_cells; i++) {
      const int cur_node = cell_list[i];
      terrain_segment *tseg = &Terrain_seg[cur_node];

      vector fpnt;
      ComputeTerrainSegmentCenter(&fpnt, cur_node);

      vector normal =
          TerrainNormals[MAX_TERRAIN_LOD - 1][cur_node].normal1 + TerrainNormals[MAX_TERRAIN_LOD - 1][cur_node].normal2;
      vm_NormalizeVector(&normal);

      if (obj->mtype.phys_info.velocity * normal <= 0.0f) {
        vector no_y_vec = pos - fpnt;
        no_y_vec.y = 0.0f;

        float dist;

        dist = vm_NormalizeVector(&no_y_vec);

        if (dist <= rad) {
          awall_dir += ((1.0f - (dist / rad)) * normal);

          if (GameTextures[Terrain_tex_seg[tseg->texseg_index].tex_index].flags &
              (TF_VOLATILE | TF_FORCEFIELD | TF_LAVA)) {
#ifdef _DEBUG
            if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
              mprintf(0, "AI Note: Danger - NEAR FORCEFIELD, VOLATILE, OR LAVA\n");
            }
#endif
            f_danger = true;
          }

          if (dist < closest_dist) {
            closest_dist = dist;
          }
        }
      }
    }
  }

  if (closest_dist <= rad) {
    vm_NormalizeVector(&awall_dir);

    float max_influence = (ROOMNUM_OUTSIDE(obj->roomnum)) ? MAX_TERRAIN_AVOID_INFLUENCE : MAX_WALL_AVOID_INFLUENCE;
    if (f_danger) {
      max_influence *= 7.1f;
    }

    float scale = (1.0f - ((closest_dist - wall_size) / (rad - wall_size))) * max_influence;
    if (scale > max_influence)
      scale = max_influence;
    *mdir += scale * awall_dir;

    if (IS_GUIDEBOT(obj) && closest_dist < 8.0f) {
      int test_time = Gametime;

      if ((test_time % GB_WALL_PULSE_INTERVAL) == 0) {
        *mdir *= 10.0f;
      }
    }

#ifdef _DEBUG
    if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
      mprintf(0, "AI Note: Avoid wall %f\n", scale);
    }
#endif

    return true;
  }

  return false;
}

#define ONE_DEGREE_ARC_COS 0.99985f
#define FIVE_DEGREE_ARC_COS 0.9962f

// NOTE: Assumes that the vector is normalized
void AITurnTowardsDir(object *obj, /*velocity *new_vel,*/ vector *goal_dir /*, bool remain_level*/, float turn_rate) {
  vector u_axis;
  matrix rot_matrix;
  angle goal_angle;
  float max_angle;

  matrix saved_orient = obj->orient;
  vector saved_uvec = obj->orient.uvec;

  if (*goal_dir == Zero_vector || (obj->orient.fvec * (*goal_dir)) >= ONE_DEGREE_ARC_COS)
    return; // No goal_dir or less than 1 degree off goal

  if (obj->size > 32.0f && (obj->orient.fvec * (*goal_dir)) >= FIVE_DEGREE_ARC_COS)
    return; // Big objects have more play

  if (obj->type != OBJ_WEAPON) {
    obj->ai_info->flags |= AIF_REPORT_NEW_ORIENT;
    if (obj->ai_info)
      obj->ai_info->saved_orient = obj->orient;
  }

  goal_angle = vm_DeltaAngVecNorm(&obj->orient.fvec, goal_dir, &u_axis);

  if (goal_angle == 0)
    return;

  max_angle = turn_rate * Frametime;

  if ((float)goal_angle > max_angle) {
    matrix turn_matrix;

    if (max_angle != 32767 && max_angle != 32768) {
      // Get the up axis
      vm_CrossProduct(&u_axis, &obj->orient.fvec, goal_dir);

      // Using the forward(original orient's forward) and the up (computed), get the orientation matrix
      vm_VectorToMatrix(&rot_matrix, &obj->orient.fvec, &u_axis, NULL);
    } else {
      rot_matrix = obj->orient;
    }

    vm_AnglesToMatrix(&turn_matrix, 0.0, max_angle, 0.0);

    rot_matrix = rot_matrix * turn_matrix;

    obj->orient.fvec = rot_matrix.fvec; // ObjSetOrient below
  } else {
    obj->orient.fvec = *goal_dir; // ObjSetOrient below
  }

  if (obj->movement_type == MT_WALKING) {
    obj->orient.uvec = saved_uvec;

    float f_proj = obj->orient.uvec * obj->orient.fvec;
    float r_proj = obj->orient.uvec * obj->orient.rvec;

    if (f_proj <= -1.0f || f_proj >= 1.0f || r_proj >= 1.0f || r_proj <= -1.0f) {
      obj->orient = saved_orient;
    } else {
      obj->orient.fvec -= (obj->orient.uvec * f_proj);
      obj->orient.rvec -= (obj->orient.uvec * r_proj);

      vm_NormalizeVector(&obj->orient.fvec);
      vm_NormalizeVector(&obj->orient.rvec);
    }
  }

  vm_Orthogonalize(&obj->orient);
  ObjSetOrient(obj, &obj->orient);
}

bool AITurnTowardsMatrix(object *obj, float turn_rate, matrix *g_orient) {
  float max_angles = turn_rate * Frametime;

  matrix t_s_matrix = obj->orient;
  vm_TransposeMatrix(&t_s_matrix);

  matrix rot_matrix;

  rot_matrix = t_s_matrix * *g_orient;

  angvec a;
  vm_ExtractAnglesFromMatrix(&a, &rot_matrix);
  vector dist;

  if (a.b > 32768)
    dist.x = 65536 - a.b;
  else
    dist.x = a.b;

  if (a.h > 32768)
    dist.y = 65536 - a.h;
  else
    dist.y = a.h;

  if (a.p > 32768)
    dist.z = 65536 - a.p;
  else
    dist.z = a.p;

  float angles = vm_GetMagnitude(&dist);

  if (angles <= max_angles) {
    obj->orient = *g_orient;
    vm_Orthogonalize(&obj->orient);
    ObjSetOrient(obj, &obj->orient);
    return true;
  }

  float scale = max_angles / angles;
  dist *= scale;

  if (a.b > 32768)
    a.b = 65535 - dist.x;
  else
    a.b = dist.x;

  if (a.h > 32768)
    a.h = 65535 - dist.y;
  else
    a.h = dist.y;

  if (a.p > 32768)
    a.p = 65535 - dist.z;
  else
    a.p = dist.z;

  vm_AnglesToMatrix(&rot_matrix, a.p, a.h, a.b);
  obj->orient *= rot_matrix;
  vm_Orthogonalize(&obj->orient);
  ObjSetOrient(obj, &obj->orient);

  return false;
}

// MTS: Unused?
void AITurnTowardsPosition(object *obj, /*velocity *new_vel,*/ vector *pos /*, bool remain_level*/) {
  vector goal_dir = *pos - obj->pos;
  ai_frame *ai_info = obj->ai_info;

  // If we want to face ourselves, we are done.  :)
  float dist = vm_NormalizeVector(&goal_dir);
  if (dist < .1f)
    return;

  AITurnTowardsDir(obj, &goal_dir, ai_info->max_turn_rate);
}

#define AI_AVE_MELEE_TIME .45f

bool MeleeHitOk(object *obj) {
  ai_frame *ai_info = obj->ai_info;
  vector intp;
  float col_dist;
  int num_attacks = 0;
  float delay = 0.0f;
  const int ai_movement = ai_info->movement_type;
  polyobj_info *p_info = &obj->rtype.pobj_info;
  float time_left;

  if (p_info->anim_end_frame != p_info->anim_start_frame) {
    float time_per_frame = p_info->anim_time / ((float)p_info->anim_end_frame - (float)p_info->anim_start_frame);

    time_left = time_per_frame * (p_info->anim_end_frame - p_info->anim_frame);
  } else {
    time_left = 0.0f;
  }

  vector relative_vel;
  vector g_end_pos;

  object *target = ObjGet(ai_info->target_handle);

  if (target == NULL || ai_info->dist_to_target_perceived > 100.0f) {
    return false;
  }

  float dist = vm_VectorDistance(&obj->pos, &target->pos);

  if (dist <= AI_MAX_MELEE_RANGE) {
    return true;
  }

  if (ai_info->flags & AIF_MELEE1) {
    num_attacks++;
    delay += Object_info[obj->id].anim[ai_movement].elem[AS_MELEE1].spc;
  }

  if (ai_info->flags & AIF_MELEE2) {
    num_attacks++;
    delay += Object_info[obj->id].anim[ai_movement].elem[AS_MELEE2].spc;
  }

  if (!num_attacks) {
    return false;
  } else if (num_attacks > 1) {
    delay = delay / (float)num_attacks;
  }

  delay += time_left + Frametime;

  // Determines the relative velocities
  if (obj->movement_type == MT_PHYSICS || obj->movement_type == MT_PHYSICS) {
    if (target->movement_type == MT_PHYSICS || target->movement_type == MT_PHYSICS) {
      relative_vel = obj->mtype.phys_info.velocity - target->mtype.phys_info.velocity;
    } else {
      relative_vel = obj->mtype.phys_info.velocity;
    }
  } else {
    if (target->movement_type == MT_PHYSICS || target->movement_type == MT_PHYSICS) {
      relative_vel = -target->mtype.phys_info.velocity;
    } else {
      relative_vel = Zero_vector;
    }
  }

  if (obj->movement_type == MT_PHYSICS || obj->movement_type == MT_PHYSICS) {
    if ((relative_vel * ai_info->vec_to_target_perceived) < 0.0f) {
      return false;
    }
  }

  g_end_pos = obj->pos + (delay * relative_vel);

  if (check_vector_to_sphere_1(&intp, &col_dist, &obj->pos, &g_end_pos, &target->pos,
                               target->size + obj->size + (.9f * AI_MAX_MELEE_RANGE), false, true) != 0) {
    return true;
  }

  return false;
}

bool AiMelee(object *obj) {
  ai_frame *ai_info = obj->ai_info;
  vector f_vec;
  float dot;

  object *target = ObjGet(ai_info->target_handle);

  if (target == NULL) {
    ai_info->status_reg &= ~AISR_MELEE;
    return false;
  }

  if (((Gametime - ai_info->last_see_target_time) > 4.0 && ((Gametime - ai_info->last_hear_target_time) > 4.0)) ||
      ai_info->awareness <= AWARE_BARELY) {
    ai_info->status_reg &= ~AISR_MELEE;
    return false;
  }

  if (ai_info->next_melee_time > Gametime) {
    ai_info->status_reg &= ~AISR_MELEE;
    return false;
  }

  if (ai_info->next_animation_type == AS_MELEE1 || ai_info->next_animation_type == AS_MELEE2) {
    ai_info->status_reg |= AISR_MELEE;
    return false;
  }

  if (!(ai_info->flags & (AIF_MELEE1 | AIF_MELEE2))) {
    ai_info->status_reg &= ~AISR_MELEE;
    return false;
  }

  // The AI wants to attack!!!!!
  ai_info->status_reg |= AISR_MELEE;

  // Determine if we are in melee range
  if (!MeleeHitOk(obj)) {
    return false;
  }

  f_vec = obj->orient.fvec;
  vm_NormalizeVector(&f_vec);

  dot = f_vec * ai_info->vec_to_target_perceived;

  if (dot >= 0.8f) {
    gi_fire attack_info;
    int attack_num;

    if (!(ai_info->flags & AIF_MELEE1) || ((ai_info->flags & AIF_MELEE2) && (ps_rand() > (D3_RAND_MAX >> 1)))) {
      attack_num = 1;
    } else {
      attack_num = 0;
    }

    //	mprintf(0, "Melee attack now!!!!\n");

    attack_info.melee_number = attack_num;
    if (GoalAddGoal(obj, AIG_DO_MELEE_ANIM, (void *)&attack_info, ACTIVATION_BLEND_LEVEL) == 0)
      return true;
  }

  return false;
}

void do_melee_attack(object *obj) {
  ai_frame *ai_info = obj->ai_info;
  float damage;
  notify melee_info;
  int attack_num;
  object *target = ObjGet(ai_info->target_handle);

  if (ai_info->animation_type == AS_MELEE1) {
    damage = ai_info->melee_damage[0];
    ai_info->next_melee_time = Gametime + ai_info->melee_latency[0];
    attack_num = 0;
  } else {
    damage = ai_info->melee_damage[1];
    ai_info->next_melee_time = Gametime + ai_info->melee_latency[1];
    attack_num = 1;
  }

  melee_info.obj_handle = ai_info->target_handle;
  melee_info.attack_num = attack_num;

  AINotify(obj, AIN_MELEE_ATTACK_FRAME, (void *)&melee_info);

  if (target) {
    float dist = ai_info->dist_to_target_actual;

    if (dist <= AI_MAX_MELEE_RANGE) {
      AINotify(obj, AIN_MELEE_HIT, (void *)&melee_info);

      if (damage >= 1.0f) {
        object *objptr = ObjGet(ai_info->target_handle);

        if (objptr) {
          if (ps_rand() > D3_RAND_MAX / 2) {
            Sound_system.Play3dSound(SOUND_MELEE_HIT_0, SND_PRIORITY_HIGHEST, objptr);
            if (Game_mode & GM_MULTI)
              MultiPlay3dSound(SOUND_MELEE_HIT_0, OBJNUM(objptr), SND_PRIORITY_HIGHEST);
            if (Demo_flags == DF_RECORDING)
              DemoWrite3DSound(SOUND_MELEE_HIT_0, OBJNUM(objptr), SND_PRIORITY_HIGHEST);
          } else {
            Sound_system.Play3dSound(SOUND_MELEE_HIT_1, SND_PRIORITY_HIGHEST, objptr);
            if (Game_mode & GM_MULTI)
              MultiPlay3dSound(SOUND_MELEE_HIT_1, OBJNUM(objptr), SND_PRIORITY_HIGHEST);
            if (Demo_flags == DF_RECORDING)
              DemoWrite3DSound(SOUND_MELEE_HIT_1, OBJNUM(objptr), SND_PRIORITY_HIGHEST);
          }

          if (objptr->type == OBJ_PLAYER)
            ApplyDamageToPlayer(objptr, obj, PD_MELEE_ATTACK, damage);
          else
            ApplyDamageToGeneric(objptr, obj, GD_MELEE_ATTACK, damage);
        }
      } else if (damage == 0.0f) {
        float energy;
        object *objptr = ObjGet(ai_info->target_handle);

        // chrishack - milestone - replace with real code
        if (objptr) {
          Sound_system.Play3dSound(SOUND_ENERGY_DRAIN, SND_PRIORITY_HIGHEST, objptr);
          if (Game_mode & GM_MULTI)
            MultiPlay3dSound(SOUND_ENERGY_DRAIN, OBJNUM(objptr), SND_PRIORITY_HIGHEST);
          if (Demo_flags == DF_RECORDING)
            DemoWrite3DSound(SOUND_ENERGY_DRAIN, OBJNUM(objptr), SND_PRIORITY_HIGHEST);

          energy = (14 + ps_rand() % 5) * Diff_general_inv_scalar[DIFF_LEVEL];

          if (objptr->type == OBJ_PLAYER) {
            if (Players[objptr->id].energy < energy)
              energy = Players[objptr->id].energy;

            DecreasePlayerEnergy(objptr->id, energy);
          }
        }
      }
    }
  }
}

void do_ranged_attack(object *obj) {
  ai_frame *ai_info = obj->ai_info;
  int cur_wb = ai_info->current_wb_firing;

  // Fire Weapon
  WBFireBattery(obj, &Object_info[obj->id].static_wb[cur_wb], cur_wb);
  ai_info->status_reg &= ~AISR_RANGED_ATTACK;
}

void AIUpdateAnim(object *obj) {
  ai_frame *ai_info = obj->ai_info;
  polyobj_info *p_info = &obj->rtype.pobj_info;
  int new_anim = ai_info->next_animation_type;
  int ai_movement = ai_info->movement_type;

  if (ai_info->anim_sound_handle != 0)
    Sound_system.StopSoundLooping(ai_info->anim_sound_handle);

  if (!Object_info[obj->id].anim)
    return;

  if ((Demo_flags == DF_PLAYBACK) || ((Game_mode & GM_MULTI) && (Netgame.local_role == LR_CLIENT))) {
    p_info->anim_flags &= ~AIAF_NOTIFY;

    if (!(p_info->multi_anim_info.flags & FMA_VALID)) {
      mprintf(0, "Update Anim: Earily bail\n");
      return;
    }

    custom_anim *multi_anim_info = &p_info->multi_anim_info;

    multi_anim_info->server_time = Gametime;
    p_info->anim_frame = ((float)multi_anim_info->server_anim_frame) / 256.0f;

    p_info->anim_start_frame = multi_anim_info->anim_start_frame;
    p_info->anim_end_frame = multi_anim_info->anim_end_frame;
    p_info->anim_time = multi_anim_info->anim_time;
    p_info->max_speed = multi_anim_info->max_speed;

    p_info->anim_flags = 0;

    if (multi_anim_info->flags & FMA_LOOPING)
      p_info->anim_flags |= AIAF_LOOPING;

    // Make sure we mark it as current and
    p_info->multi_anim_info.flags |= FMA_CURRENT;

    if (multi_anim_info->anim_sound_index >= 0) {
      Sound_system.StopSoundLooping(ai_info->anim_sound_handle);
      ai_info->anim_sound_handle = Sound_system.Play3dSound(multi_anim_info->anim_sound_index, SND_PRIORITY_LOW, obj);
    }

    return;
  }

  if (new_anim == AS_FLINCH) {
    float delta_time = 1.0f + obj->shields / 10.0f;
    if (delta_time > 4.3) {
      delta_time = 4.3f;
    }

    ai_info->next_flinch_time = Gametime + delta_time;
  }
  //	mprintf(0, "D %d to %d\n", ai_info->animation_type, ai_info->next_animation_type);

  // Update the physics and movement class info
  switch (ai_info->animation_type) {
  case AS_GOTO_IDLE_STANDING:
  case AS_GOTO_ALERT_STANDING:
    if (obj->movement_type != MT_NONE)
      obj->movement_type = MT_WALKING;
    ai_movement = ai_info->movement_type = MC_STANDING;
    break;

  case AS_GOTO_IDLE_FLYING:
  case AS_GOTO_ALERT_FLYING:
    obj->movement_type = MT_PHYSICS;
    ai_movement = ai_info->movement_type = MC_FLYING;
    break;

  case AS_GOTO_IDLE_ROLLING:
  case AS_GOTO_ALERT_ROLLING:
    obj->movement_type = MT_WALKING;
    ai_movement = ai_info->movement_type = MC_ROLLING;
    break;

  case AS_GOTO_IDLE_WALKING:
  case AS_GOTO_ALERT_WALKING:
    obj->movement_type = MT_WALKING;
    ai_movement = ai_info->movement_type = MC_WALKING;
    break;

  case AS_GOTO_IDLE_JUMPING:
  case AS_GOTO_ALERT_JUMPING:
    obj->movement_type = MT_PHYSICS;
    ai_movement = ai_info->movement_type = MC_JUMPING;
    break;
  }

  if (new_anim == AS_RANGED_ATTACK) {
    if (ai_info->sound[AI_ATTACK_SOUND] != SOUND_NONE_INDEX) {
      // Plays the sound and makes absolute sure that it is not looping
      if (Gametime - ai_info->last_sound_time[AI_ATTACK_SOUND] > 5.0f) {
        // A 75% chance of playing it
        if (ps_rand() % 4 != 0) {
          Sound_system.StopSoundLooping(
              Sound_system.Play3dSound(ai_info->sound[AI_ATTACK_SOUND], SND_PRIORITY_NORMAL, obj));
          if (Game_mode & GM_MULTI)
            MultiPlay3dSound(ai_info->sound[AI_ATTACK_SOUND], OBJNUM(obj), SND_PRIORITY_NORMAL);
          if (Demo_flags == DF_RECORDING)
            DemoWrite3DSound(ai_info->sound[AI_ATTACK_SOUND], OBJNUM(obj), SND_PRIORITY_NORMAL);
        }
        ai_info->last_sound_time[AI_ATTACK_SOUND] = Gametime;
      }
    }
  } else if (new_anim != AI_INVALID_INDEX && new_anim != AS_RANGED_RECOIL) {
    if ((new_anim != AS_CUSTOM &&
         Object_info[obj->id].anim[ai_movement].elem[new_anim].anim_sound_index != SOUND_NONE_INDEX) ||
        (new_anim == AS_CUSTOM && p_info->custom_anim_info.anim_sound_index != SOUND_NONE_INDEX)) {
      if (new_anim != AS_CUSTOM)
        ai_info->last_played_sound_index = Object_info[obj->id].anim[ai_movement].elem[new_anim].anim_sound_index;
      else
        ai_info->last_played_sound_index = p_info->custom_anim_info.anim_sound_index;

      ai_info->anim_sound_handle = Sound_system.Play3dSound(ai_info->last_played_sound_index, SND_PRIORITY_LOW, obj);
    } else {
      ai_info->last_played_sound_index = -1;
    }
  }

new_anim_label:

  if (new_anim != AI_INVALID_INDEX) {
    // Melee stuff
    if (ai_info->animation_type == AS_MELEE1 || ai_info->animation_type == AS_MELEE2) {
      do_melee_attack(obj);
    } else if (ai_info->animation_type == AS_RANGED_ATTACK) {
      ASSERT(new_anim == AS_RANGED_RECOIL);

      int cur_wb = ai_info->current_wb_firing;
      int cur_mask = obj->dynamic_wb[cur_wb].wb_anim_mask;
      float fire = Object_info[obj->id].static_wb[cur_wb].anim_fire_frame[cur_mask];

      float temp_anim = p_info->anim_frame;
      p_info->anim_frame = fire;
      do_ranged_attack(obj);
      p_info->anim_frame = temp_anim;
    }

    // Set the new animation
    ai_info->animation_type = new_anim;

    if (new_anim == AS_RANGED_ATTACK) {
      int cur_wb = ai_info->current_wb_firing;
      int cur_mask = obj->dynamic_wb[cur_wb].wb_anim_mask;

      float start = Object_info[obj->id].static_wb[cur_wb].anim_start_frame[cur_mask];
      float fire = Object_info[obj->id].static_wb[cur_wb].anim_fire_frame[cur_mask];
      float end = Object_info[obj->id].static_wb[cur_wb].anim_end_frame[cur_mask];
      float total_time = Object_info[obj->id].static_wb[cur_wb].anim_time[cur_mask];

      p_info->anim_start_frame = start;
      p_info->anim_end_frame = fire;

      if (start < fire) {
        p_info->anim_time = total_time * ((fire - start) / (end - start));
      } else {
        new_anim = AS_RANGED_RECOIL;
        goto new_anim_label;
      }
    } else if (new_anim == AS_RANGED_RECOIL) {
      int cur_wb = ai_info->current_wb_firing;
      int cur_mask = obj->dynamic_wb[cur_wb].wb_anim_mask;

      float start = Object_info[obj->id].static_wb[cur_wb].anim_start_frame[cur_mask];
      float fire = Object_info[obj->id].static_wb[cur_wb].anim_fire_frame[cur_mask];
      float end = Object_info[obj->id].static_wb[cur_wb].anim_end_frame[cur_mask];
      float total_time = Object_info[obj->id].static_wb[cur_wb].anim_time[cur_mask];

      p_info->anim_start_frame = fire;
      p_info->anim_end_frame = end;

      if (fire < end)
        p_info->anim_time = total_time * ((end - fire) / (end - start));
      else {
        new_anim = AS_ALERT;
        goto new_anim_label;
      }
    } else if (new_anim == AS_CUSTOM) {
      p_info->anim_start_frame = p_info->custom_anim_info.anim_start_frame;
      p_info->anim_end_frame = p_info->custom_anim_info.anim_end_frame;
      p_info->anim_time = p_info->custom_anim_info.anim_time;
      p_info->anim_flags = p_info->custom_anim_info.flags;
      ai_info->next_animation_type = p_info->custom_anim_info.next_anim_type;
    } else {
      p_info->anim_start_frame = Object_info[obj->id].anim[ai_movement].elem[new_anim].from;
      p_info->anim_end_frame = Object_info[obj->id].anim[ai_movement].elem[new_anim].to;
      p_info->anim_time = Object_info[obj->id].anim[ai_movement].elem[new_anim].spc;
    }

    p_info->anim_frame = p_info->anim_start_frame;

    // Handle the next anim's
    switch (new_anim) {
    case AS_MELEE1:
    case AS_MELEE2: {
      p_info->anim_flags = AIAF_NOTIFY;
      ai_info->next_animation_type = new_anim + 1; /* Recoil */
    } break;

    case AS_RANGED_ATTACK: {
      p_info->anim_flags = AIAF_NOTIFY;
      ai_info->next_animation_type = AS_RANGED_RECOIL; /* Recoil */
    } break;

    case AS_DEATH: {
      p_info->anim_flags = 0;
      ai_info->next_animation_type = AI_INVALID_INDEX;
    } break;

    case AS_ALERT:
    case AS_IDLE: {
      p_info->anim_flags = AIAF_LOOPING;
      ai_info->next_animation_type = AI_INVALID_INDEX;
    } break;

    case (AS_MELEE1 + 1):

    {
      if (!AiMelee(obj)) {
        p_info->anim_flags = AIAF_NOTIFY;
        ai_info->next_animation_type = AS_ALERT;
      }
    } break;

    case (AS_MELEE2 + 1): {
      if (!AiMelee(obj)) {
        p_info->anim_flags = AIAF_NOTIFY;
        ai_info->next_animation_type = AS_ALERT;
      }
    } break;

    case AS_GOTO_IDLE_STANDING:
    case AS_GOTO_IDLE_FLYING:
    case AS_GOTO_IDLE_ROLLING:
    case AS_GOTO_IDLE_WALKING:
    case AS_GOTO_IDLE_JUMPING:
    case AS_QUIRK:
    case AS_BIRTH: {
      p_info->anim_flags = AIAF_NOTIFY;
      ai_info->next_animation_type = AS_IDLE;
    } break;

    case AS_CUSTOM:
      break;

    default: {
      p_info->anim_flags = AIAF_NOTIFY;
      ai_info->next_animation_type = AS_ALERT;
    } break;
    }
  }

  if ((Game_mode & GM_MULTI) && (Netgame.local_role == LR_SERVER)) {
    MultiAddObjAnimUpdate(OBJNUM(obj));
  }
  if (Demo_flags == DF_RECORDING) {
    DemoWriteObjAnimChanged(OBJNUM(obj));
  }
}

static inline void ApplyConstantForce(object *objp, vector *new_pos, vector *force, float delta_time) {
  const vector velocity = objp->mtype.phys_info.velocity;
  const float drag = objp->mtype.phys_info.drag;
  const float mass = objp->mtype.phys_info.mass;

  // Standard motion with a linear air drag (drag is proportional to velocity)
  *new_pos = objp->pos + (*force / drag) * (delta_time) +
             (mass / drag) * (velocity - (*force / drag)) * (1 - exp(-(drag / mass) * delta_time));
}

bool AIDetermineAimPoint(object *robot, object *target, vector *aim_pt, float weapon_speed) {
  if (DIFF_LEVEL == DIFFICULTY_TRAINEE && ((robot->ai_info->flags & AIF_TEAM_MASK) != AIF_TEAM_REBEL)) {
    *aim_pt = target->pos;
    return true;
  }

  float vl = AIDetermineObjVisLevel(robot, target);

  ai_frame *ai_info = robot->ai_info;
  vector to_target = target->pos - robot->pos;
  float dist_to_target = vm_NormalizeVector(&to_target);

  if (weapon_speed == 0.0f && ai_info)
    weapon_speed = ai_info->weapon_speed;

  if (weapon_speed == 0.0f) {
    *aim_pt = target->pos;
    return false;
  }

  float wsp = weapon_speed - (to_target * target->mtype.phys_info.velocity);

  if (wsp <= 0.0f || vl < AIVIS_BARELY) {
    *aim_pt = target->pos;
    return false;
  }

  float dt = dist_to_target / wsp;

  float scale;

  if (ai_info)
    scale = ai_info->lead_accuracy;
  else
    scale = 1.0f;

  // chrishack -- add stuff so that rebels get better as DIFF lowers and
  // ptmc gets better as DIFF increases
  if (target->type != OBJ_PLAYER ||
      (DIFF_LEVEL < DIFFICULTY_HOTSHOT && ((robot->ai_info->flags & AIF_TEAM_MASK) != AIF_TEAM_REBEL)) ||
      scale < 0.4f || vl <= AIVIS_MOSTLY)
    *aim_pt = target->pos + (target->mtype.phys_info.velocity * dt) * scale;
  else
    ApplyConstantForce(target, aim_pt, &target->mtype.phys_info.thrust, dt * scale);

  return true;
}

vector *AIDetermineFovVec(object *obj, vector *fov) {
  ai_frame *ai_info = obj->ai_info;
  poly_model *pm = &Poly_models[obj->rtype.pobj_info.model_num];

  if ((ai_info->flags & AIF_AIM_PNT_FOV) && pm->num_wbs > 0) {
    int aiming_gp_index = Object_info[obj->id].static_wb[0].aiming_gp_index;
    WeaponCalcGun(NULL, fov, obj, pm->poly_wb[0].gp_index[aiming_gp_index]);
  } else if (ai_info->flags & AIF_UVEC_FOV) {
    *fov = obj->orient.uvec;
  } else {
    *fov = obj->orient.fvec;
  }

  return fov;
}

#ifdef _DEBUG
extern int DoAI;
#else
#define DoAI 1
#endif

void AISeeTarget(object *obj, bool f_see) {
  ai_frame *ai_info = obj->ai_info;

  if (f_see) {
    if ((Gametime - ai_info->last_see_target_time > CHECK_VIS_INFREQUENTLY_TIME) || !(ai_info->awareness)) {
      if (ai_info->sound[AI_SEE_SOUND] != SOUND_NONE_INDEX) {
        // Plays the sound and makes absolute sure that it is not looping
        if ((ps_rand() % 10) != 0) // 90% chance of playing it
        {
          if (Gametime - ai_info->last_sound_time[AI_SEE_SOUND] >= CHECK_VIS_INFREQUENTLY_TIME) {
            Sound_system.StopSoundLooping(
                Sound_system.Play3dSound(ai_info->sound[AI_SEE_SOUND], SND_PRIORITY_NORMAL, obj));
            if (Game_mode & GM_MULTI)
              MultiPlay3dSound(ai_info->sound[AI_SEE_SOUND], OBJNUM(obj), SND_PRIORITY_LOW);
            if (Demo_flags == DF_RECORDING)
              DemoWrite3DSound(ai_info->sound[AI_SEE_SOUND], OBJNUM(obj), SND_PRIORITY_LOW);
          }
        }

        ai_info->last_sound_time[AI_SEE_SOUND] = Gametime;
      }
    }
  }

  if (ai_info->awareness < AWARE_MOSTLY)
    ai_info->awareness = AWARE_MOSTLY;

  // Note:  Player position is also updated in the visability test function
  //        for MIN_VIS_RECENT_CHECK_INTERVAL seconds
  object *targetptr;
  object *other_obj = targetptr = ObjGet(ai_info->target_handle);

  if (targetptr) {
    if (f_see)
      ai_info->last_see_target_time = Gametime;
    else
      ai_info->last_hear_target_time = Gametime;

    AIDetermineAimPoint(obj, targetptr, &ai_info->last_see_target_pos);
  }
}

bool AINotify(object *obj, uint8_t notify_type, void *info) {
  int next_anim;
  ai_frame *ai_info = obj->ai_info;
  //@$-tD3XEventArgs evtargs;
  object *other_obj = NULL;
  object *targetptr;
  int parent;
  object *new_enemy;
  tOSIRISEventInfo ei;
  bool f_it_set = false;

  if (Demo_flags == DF_PLAYBACK) {
    return false;
  }
  ASSERT(obj);
  ASSERT(notify_type >= 0 && notify_type < 32);

  if (((Game_mode & GM_MULTI) && (Netgame.local_role == LR_CLIENT)))
    return false;

  if (!DoAI)
    return false;

  if (obj->type == OBJ_DUMMY && notify_type != AIN_USER_DEFINED)
    return false;

  if (obj && obj->control_type == CT_AI && ai_info->flags & AIF_DISABLED)
    return false;

  // All events use
  //@$-evtargs.args[0] = MAKE_NUM_EVTARG((float)notify_type);
  ei.evt_ai_notify.notify_type = notify_type;

  switch (notify_type) {
  case AIN_ANIM_COMPLETE:
    if (ai_info->notify_flags & (0x00000001 << notify_type)) {
      AIUpdateAnim(obj);
    }
    break; // parent robot
  case AIN_SCRIPTED_ENABLER: {
    //@$-evtargs.args[1] = MAKE_NUM_EVTARG(((notify *)info)->goal_num);
    //@$-evtargs.args[2] = MAKE_NUM_EVTARG(((notify *)info)->enabler_num);
    ei.evt_ai_notify.goal_num = ((notify *)info)->goal_num;
    ei.evt_ai_notify.enabler_num = ((notify *)info)->enabler_num;
  } break;
  case AIN_NEW_MOVEMENT:
    break; // parent robot
  case AIN_OBJ_KILLED:
    break; // parent robot
  case AIN_MELEE_HIT:
  case AIN_MELEE_ATTACK_FRAME: {
    notify *melee_info = (notify *)info;

    other_obj = ObjGet(melee_info->obj_handle);

    //@$-evtargs.args[1] = MAKE_NUM_EVTARG(((notify *)info)->attack_num);
    ei.evt_ai_notify.attack_num = melee_info->attack_num;
  } break;
  case AIN_WHIT_BY_OBJ:
    break;             // parent robot
  case AIN_SEE_TARGET: // parent robot	  (who sees, type, player_obj)
    if (ai_info->notify_flags & (0x00000001 << notify_type)) {
      AISeeTarget(obj, true);
    }
    other_obj = (object *)info;
    break;
  case AIN_PLAYER_SEES_YOU: // parent robot  (who got seen, type, player_obj)
    if (ai_info->notify_flags & (0x00000001 << notify_type)) {
      if (ai_info->awareness < AWARE_BARELY)
        ai_info->awareness = AWARE_BARELY;
      ai_info->last_render_time = Gametime;
    }
    break;
  case AIN_WHIT_OBJECT: // A robots (the one being notified, hit something) --chrishack -- if friend, no fire for X
                        // seconds

    ai_info->memory[0].num_hit_enemy++;

    if (ai_info->awareness < AWARE_MOSTLY) {
      ai_info->awareness = AWARE_MOSTLY;
    }
    // chrishack -- if hitobject is target then...  But, this is ok for now
    targetptr = ObjGet(ai_info->target_handle);

    // chrishack - not really done - quick implementation
    if (targetptr) {
      ai_info->last_see_target_time = Gametime;
      AIDetermineAimPoint(obj, targetptr, &ai_info->last_see_target_pos);
    }

    // chrishack!
    other_obj = (object *)info;
    break;

  case AIN_MOVIE_START:
  case AIN_MOVIE_END:
    break;
  case AIN_TARGET_DIED:
    ei.evt_ai_notify.it_handle = *(int *)info;
    f_it_set = true;
    break;

  case AIN_OBJ_FIRED: // All visable  (obj fired, AIN_OBJFIRED, obj who fired) -- all rendered bots
  {
    int i;
    other_obj = (object *)info;
    object *targetptr;

    if (other_obj->control_type == CT_AI) {
      tOSIRISEventInfo ei;

      ei.evt_ai_notify.notify_type = AIN_FIRED_WEAPON;
      ei.evt_ai_notify.attack_num = obj->ctype.laser_info.src_gun_num;
      ei.evt_ai_notify.it_handle = obj->handle;

      Osiris_CallEvent(other_obj, EVT_AI_NOTIFY, &ei);
    }

    if (other_obj->type == OBJ_PLAYER) {
      ain_hear hear;

      hear.f_directly_player = true;
      hear.hostile_level = 1.0f;
      hear.curiosity_level = 0.0f;
      hear.max_dist = AI_SOUND_SHORT_DIST;
      AINotify(other_obj, AIN_HEAR_NOISE, (void *)&hear);
    }

    if (other_obj->control_type == CT_AI) {
      targetptr = ObjGet(other_obj->ai_info->target_handle);
    } else {
      targetptr = NULL;
    }

    // CHRISHACK - WTF - What was this actually for????  Hmmm.....
    //			if(obj == targetptr)
    //			{
    //				ei.evt_ai_notify.it_handle = ai_info->target_handle;
    //
    //				ai_info->memory[0].num_enemy_shots_fired++;
    //
    //				//@$-D3XExecScript(obj, EVT_AI_NOTIFY, obj, REF_OBJTYPE, &evtargs);
    //				Osiris_CallEvent(obj,EVT_AI_NOTIFY,&ei);
    //			}

    if (targetptr && targetptr->control_type == CT_AI) {
      if ((targetptr->ai_info->flags & AIF_DODGE) && !(IS_GUIDEBOT(targetptr))) {
        if (BOA_IsVisible(targetptr->roomnum, other_obj->roomnum)) {
          targetptr->ai_info->memory[0].num_enemy_shots_dodged++;
          GoalAddGoal(targetptr, AIG_DODGE_OBJ, (void *)&obj->handle, ACTIVATION_BLEND_LEVEL);

          //@$-D3XExecScript(targetptr, EVT_AI_NOTIFY, obj, REF_OBJTYPE, &evtargs);
          ei.evt_ai_notify.it_handle = obj->handle;
          Osiris_CallEvent(targetptr, EVT_AI_NOTIFY, &ei);
        }
      }
    } else if (other_obj->type == OBJ_PLAYER) // chrishack -- we might be able use the target handle and last see time!
                                              // use BOA line-of-sight if any player then notify!  Damn big improvement.
    {
      if (!(Game_mode & GM_MULTI)) {
        for (i = 0; i < AI_NumRendered; i++) {
        // mprintf(0, "I know that I could dodge, if I was aware, says robot %d.\n", AI_RenderedList[i]);

          if (!BOA_IsVisible(Objects[AI_RenderedList[i]].roomnum, other_obj->roomnum))
            continue;

          ai_frame *ai_info = Objects[AI_RenderedList[i]].ai_info;
          if (ai_info->notify_flags & (0x00000001 << notify_type)) {
            if (!(ai_info->flags & AIF_DISABLED)) {
              if (ai_info->flags & AIF_DODGE) {
                if (ai_info->awareness > AWARE_BARELY) {
                  if (ps_rand() < ai_info->dodge_percent * D3_RAND_MAX) {
                    vector fov_vec;

                    if (ai_info->vec_to_target_actual * (*AIDetermineFovVec(&Objects[AI_RenderedList[i]], &fov_vec)) >=
                        Objects[AI_RenderedList[i]].ai_info->fov) {
                      // mprintf(0, "I am fired upon says robot %d\n", AI_RenderedList[i]));
                      if (ai_info->notify_flags & (0x00000001 << notify_type)) {
                        ai_info->memory[0].num_enemy_shots_dodged++;
                        GoalAddGoal(&Objects[AI_RenderedList[i]], AIG_DODGE_OBJ, (void *)&obj->handle,
                                    ACTIVATION_BLEND_LEVEL, 1.0f, GF_SPEED_DODGE);
                      }
                    }
                  }
                }
              }
            }
          }
          //@$-D3XExecScript(&Objects[AI_RenderedList[i]], EVT_AI_NOTIFY, NULL, REF_OBJTYPE, &evtargs);
          Osiris_CallEvent(&Objects[AI_RenderedList[i]], EVT_AI_NOTIFY, &ei);

          // This might be removed
          AISeeTarget(&Objects[AI_RenderedList[i]], false);
        }
      } else {
        for (i = 0; i <= Highest_object_index; i++) {
          // mprintf(0, "I know that I could dodge, if I was aware, says robot %d.\n", AI_RenderedList[i]);
          if (Objects[i].control_type != CT_AI || Objects[i].type == OBJ_NONE)
            continue;

          if (!BOA_IsVisible(Objects[i].roomnum, other_obj->roomnum))
            continue;

          ai_frame *ai_info = Objects[i].ai_info;

          if (ai_info->notify_flags & (0x00000001 << notify_type)) {
            if (!(ai_info->flags & AIF_DISABLED)) {
              if (ai_info->flags & AIF_DODGE) {
                if (ps_rand() < ai_info->dodge_percent * D3_RAND_MAX) {
                  vector to_weapon = other_obj->pos - Objects[i].pos;
                  vm_NormalizeVector(&to_weapon);

                  vector fov_vec;
                  AIDetermineFovVec(&Objects[i], &fov_vec);

                  if (to_weapon * fov_vec >= Objects[i].ai_info->fov) {
                    // mprintf(0, "I am fired upon says robot %d\n", AI_RenderedList[i]);
                    if (ai_info->notify_flags & (0x00000001 << notify_type)) {
                      ai_info->memory[0].num_enemy_shots_dodged++;
                      GoalAddGoal(&Objects[i], AIG_DODGE_OBJ, (void *)&obj->handle, ACTIVATION_BLEND_LEVEL, 1.0f,
                                  GF_SPEED_DODGE);
                    }
                  }
                }
              }
            }
          }
          //@$-D3XExecScript(&Objects[i], EVT_AI_NOTIFY, NULL, REF_OBJTYPE, &evtargs);
          Osiris_CallEvent(&Objects[i], EVT_AI_NOTIFY, &ei);

          // This might be removed
          AISeeTarget(&Objects[i], false);
        }
      }
    }
  } break;
  case AIN_GOAL_COMPLETE:
  case AIN_GOAL_INVALID:
  case AIN_GOAL_FAIL:
  case AIN_GOAL_ERROR:
  case AIN_SCRIPTED_GOAL:
  case AIN_SCRIPTED_INFLUENCE:
  case AIN_SCRIPTED_ORIENT:
    ei.evt_ai_notify.goal_num = *((int *)info);
    ei.evt_ai_notify.goal_uid = ai_info->goals[ei.evt_ai_notify.goal_num].guid;
    ei.evt_ai_notify.it_handle = obj->handle;
    f_it_set = true;
    Osiris_CallLevelEvent(EVT_AI_NOTIFY, &ei);
    break;
  case AIN_HEAR_NOISE: {
    ain_hear *hptr = (ain_hear *)info;
    int i;

    if (hptr->f_directly_player) {
      int16_t heard_noise_obj[50];
      int num_objs = fvi_QuickDistObjectList(&obj->pos, obj->roomnum, hptr->max_dist, heard_noise_obj, 50, false, true,
                                             false, true);

      for (i = 0; i < num_objs; i++) {
        if (Objects[heard_noise_obj[i]].control_type == CT_AI) {
          if (vm_VectorDistance(&obj->pos, &Objects[heard_noise_obj[i]].pos) <
              hptr->max_dist * Objects[heard_noise_obj[i]].ai_info->hearing) {
            AISeeTarget(&Objects[heard_noise_obj[i]], false);
          }
        }
      }
    }
  } break; // parent robot -- chrishack -- Not done
  case AIN_NEAR_TARGET:
    other_obj = (object *)info;
    break;
  case AIN_HIT_BY_WEAPON: {
    ai_info->memory[0].num_times_hit++;

    if (ai_info->notify_flags & (0x00000001 << notify_type)) {
      ai_info->awareness = AWARE_FULLY;

      // Flinching
      if (Gametime > ai_info->next_flinch_time) {
        if (ps_rand() % 10 > 8) {
          if (ai_info->flags & AIF_FLINCH) {
            next_anim = AS_FLINCH;
            GoalAddGoal(obj, AIG_SET_ANIM, (void *)&next_anim, ACTIVATION_BLEND_LEVEL);
          }
        }
      }
    }

    if (ai_info->sound[AI_ANGRY_SOUND] != SOUND_NONE_INDEX) {
      // Plays the sound and makes absolute sure that it is not looping
      if (Gametime - ai_info->last_sound_time[AI_ANGRY_SOUND] > 5.0f) {
        Sound_system.StopSoundLooping(
            Sound_system.Play3dSound(ai_info->sound[AI_ANGRY_SOUND], SND_PRIORITY_NORMAL, obj));
        if (Game_mode & GM_MULTI)
          MultiPlay3dSound(ai_info->sound[AI_ANGRY_SOUND], OBJNUM(obj), SND_PRIORITY_NORMAL);
        if (Demo_flags == DF_RECORDING)
          DemoWrite3DSound(ai_info->sound[AI_ANGRY_SOUND], OBJNUM(obj), SND_PRIORITY_NORMAL);
        ai_info->last_sound_time[AI_ANGRY_SOUND] = Gametime;
      }
    }

    other_obj = (object *)info;
    parent = other_obj->parent_handle;
    new_enemy = ObjGet(parent);

    if (ai_info->flags & AIF_ACT_AS_NEUTRAL_UNTIL_SHOT) {
      ai_info->flags &= ~AIF_ACT_AS_NEUTRAL_UNTIL_SHOT;
      if (!AIObjEnemy(obj, new_enemy)) {
        ai_info->flags |= AIF_ACT_AS_NEUTRAL_UNTIL_SHOT;
      }
    }

    bool f_enemy = AIObjEnemy(obj, new_enemy);

    float rand_val = ps_rand() / (float)D3_RAND_MAX;

    if (new_enemy && (new_enemy != obj)) {
      // 20% per hit of switching to hitting player
      if ((new_enemy->control_type == CT_AI &&
           ((new_enemy->ai_info->target_handle == obj->handle) ||
            (!f_enemy && new_enemy->id == obj->id && new_enemy->type == obj->type && rand_val < ai_info->fight_same) ||
            (!f_enemy && !(new_enemy->id == obj->id && new_enemy->type == obj->type) &&
             rand_val < ai_info->fight_team))) ||
          (f_enemy && new_enemy->type == OBJ_PLAYER &&
           (ai_info->awareness <= AWARE_BARELY || rand_val > .8 || ai_info->target_handle == OBJECT_HANDLE_NONE))) {
        //					if(obj->ai_info->flags & AIF_DETERMINE_TARGET)
        {
          ai_info->flags |= AIF_DETERMINE_TARGET;
          obj->ai_info->next_target_update_time =
              Gametime + MIN_TARGET_UPDATE_INTERVAL +
              ((float)ps_rand() / (float)D3_RAND_MAX) * (MAX_TARGET_UPDATE_INTERVAL - MIN_TARGET_UPDATE_INTERVAL);
          AISetTarget(obj, new_enemy->handle);
        }
      }
    }
  } break;

  case AIN_BUMPED_OBJ:
    other_obj = (object *)info;

    // 100% is previously not aware, 50% if already aware
    if (AIObjEnemy(obj, other_obj)) {
      if ((ai_info->awareness <= AWARE_BARELY) || ((ai_info->awareness > AWARE_BARELY) && ((ps_rand() % 100) > 50))) {
        //					if(ai_info->flags & AIF_DETERMINE_TARGET)
        {
          ai_info->flags |= AIF_DETERMINE_TARGET;
          ai_info->next_target_update_time =
              Gametime + MIN_TARGET_UPDATE_INTERVAL +
              ((float)ps_rand() / (float)D3_RAND_MAX) * (MAX_TARGET_UPDATE_INTERVAL - MIN_TARGET_UPDATE_INTERVAL);
          AISetTarget(obj, other_obj->handle);
        }
      }

      if (ai_info->notify_flags & (0x00000001 << notify_type)) {
        ai_info->awareness = AWARE_FULLY;
        AISeeTarget(obj, false);
      }
    }

    if (ai_info->sound[AI_ANGRY_SOUND] != SOUND_NONE_INDEX) {
      // Plays the sound and makes absolute sure that it is not looping
      if (Gametime - ai_info->last_sound_time[AI_ANGRY_SOUND] > 5.0f) {
        Sound_system.StopSoundLooping(
            Sound_system.Play3dSound(ai_info->sound[AI_ANGRY_SOUND], SND_PRIORITY_NORMAL, obj));
        if (Game_mode & GM_MULTI)
          MultiPlay3dSound(ai_info->sound[AI_ANGRY_SOUND], OBJNUM(obj), SND_PRIORITY_NORMAL);
        if (Demo_flags == DF_RECORDING)
          DemoWrite3DSound(ai_info->sound[AI_ANGRY_SOUND], OBJNUM(obj), SND_PRIORITY_NORMAL);
        ai_info->last_sound_time[AI_ANGRY_SOUND] = Gametime;
      }
    }
    break;
  case AIN_USER_DEFINED:
    //@$-evtargs.args[1] = MAKE_NUM_EVTARG((float)(*((int *)info)));
    ei.extra_info = info;
    break;
  default:
    mprintf(0, "Warning, %d has been notified with an unhandled notification %d\n", OBJNUM(obj), notify_type);
    return true;
  }

  if (notify_type != AIN_OBJ_FIRED && notify_type != AIN_HEAR_NOISE) {
    //@$-return (D3XExecScript(obj, EVT_AI_NOTIFY, other_obj, REF_OBJTYPE, &evtargs));
    if (!f_it_set) {
      ei.evt_ai_notify.it_handle = ((other_obj != NULL) ? other_obj->handle : OBJECT_HANDLE_NONE);
    }

    return Osiris_CallEvent(obj, EVT_AI_NOTIFY, &ei);
  }

  return true;
}

// Returns the amount of time left
void ai_do_animation(object *obj, float anim_time) {
  float *anim_frame = &obj->rtype.pobj_info.anim_frame;

  float to;
  float from;
  float delta;
  float spc;
  bool f_looped;
  bool f_notify;
  int i;

  poly_model *pm = &Poly_models[obj->rtype.pobj_info.model_num];
  polyobj_info *p_info = &obj->rtype.pobj_info;

  if (!(Object_info[obj->id].anim))
    return;

  if ((Demo_flags == DF_PLAYBACK) || ((Game_mode & GM_MULTI) && (Netgame.local_role == LR_CLIENT))) {

    // Update animation keyframe
    if (p_info->multi_anim_info.flags & FMA_VALID) {
      if (!(p_info->multi_anim_info.flags & FMA_CURRENT)) {
        AIUpdateAnim(obj);
      }
    }

    if (p_info->multi_turret_info.flags & (FMT_UPDATING | FMT_NEW_DATA)) {
      int count = 0;
      int i, j;
      if (p_info->multi_turret_info.flags & FMT_NEW_DATA) {
        for (i = 0; i < pm->num_wbs; i++) {
          for (j = 0; j < pm->poly_wb[i].num_turrets; j++) {
            p_info->multi_turret_info.last_time = Gametime;
            p_info->multi_turret_info.last_keyframes[count++] = obj->dynamic_wb[i].norm_turret_angle[j];
          }
        }

        p_info->multi_turret_info.flags = FMT_UPDATING;
      }

      count = 0;

      if ((Demo_flags == DF_PLAYBACK) ||
          ((p_info->multi_turret_info.last_time + 1.0 / (float)NetPlayers[Player_num].pps) >= Gametime)) {
        for (i = 0; i < pm->num_wbs; i++) {
          for (j = 0; j < pm->poly_wb[i].num_turrets; j++) {
            obj->dynamic_wb[i].norm_turret_angle[j] = p_info->multi_turret_info.keyframes[count++];
          }
        }

        p_info->multi_turret_info.flags = 0;
      } else {
        for (i = 0; i < pm->num_wbs; i++) {
          for (j = 0; j < pm->poly_wb[i].num_turrets; j++) {
            float pd = (Gametime - p_info->multi_turret_info.last_time) / NetPlayers[Player_num].pps;
            float diff;

            diff = p_info->multi_turret_info.keyframes[count] - p_info->multi_turret_info.last_keyframes[count];

            if (fabsf(diff) < 0.5f) {
              obj->dynamic_wb[i].norm_turret_angle[j] = (1.0 - pd) * p_info->multi_turret_info.last_keyframes[count] +
                                                        pd * p_info->multi_turret_info.keyframes[count];
            } else {
              diff = -(1.0f - diff) * pd;
              obj->dynamic_wb[i].norm_turret_angle[j] = p_info->multi_turret_info.last_keyframes[count] + diff;

              if (obj->dynamic_wb[i].norm_turret_angle[j] < 0.0)
                obj->dynamic_wb[i].norm_turret_angle[j] += 1.0f;
              else if (obj->dynamic_wb[i].norm_turret_angle[j] > 1.0)
                obj->dynamic_wb[i].norm_turret_angle[j] -= 1.0f;
            }

            count++;
          }
        }
      }
    }
  } else {
    if (obj->ai_info->animation_type == AS_RANGED_ATTACK) {
      char wb = obj->ai_info->last_special_wb_firing;

      if (Object_info[obj->id].static_wb[wb].flags & WBF_SPRAY) {
        obj->weapon_fire_flags |= WFF_SPRAY;
      }

      if (Object_info[obj->id].static_wb[wb].flags & WBF_ON_OFF) {
        obj->weapon_fire_flags |= WFF_ON_OFF;
      }
      if (Demo_flags == DF_RECORDING) {
        DemoWriteObjWeapFireFlagChanged(OBJNUM(obj));
      }
    }
  }

  for (i = 0; i < pm->num_wbs; i++) {
    if (obj->dynamic_wb[i].flags & DWBF_ANIMATING) {
      object_info *obj_info = &Object_info[obj->id];
      if (obj_info->static_wb)
        WBFireAnimFrame(obj, &obj_info->static_wb[i], i);
    }
  }

start_loop:

  from = obj->rtype.pobj_info.anim_start_frame;
  to = obj->rtype.pobj_info.anim_end_frame;
  spc = obj->rtype.pobj_info.anim_time;

  if (obj->movement_type == MT_WALKING && obj->ai_info->movement_type == MC_WALKING) {
    if (obj->ai_info->animation_type == AS_ALERT || obj->ai_info->animation_type == AS_IDLE) {
      float scaler;

      float speed = vm_GetMagnitude(&obj->mtype.phys_info.velocity);
      scaler = speed / obj->ai_info->max_velocity;

      // If slow, use some rotational vel
      if (scaler < .7f) {
        float speed = vm_GetMagnitude(&obj->mtype.phys_info.rotvel);
        scaler += speed / 40000.0f;

        if (scaler > 1.0f)
          scaler = 1.0f;
      }

      if ((obj->ai_info->next_animation_type == AS_GOTO_ALERT_STANDING ||
           obj->ai_info->next_animation_type == AS_GOTO_IDLE_STANDING) &&
          scaler < .15f) {
        scaler = .15f;
      }

      if (scaler <= 0.0f) {
        return;
      }

      spc /= scaler;
    }
  }
  // mprintf(0, "AI ANIM %d %d\n", from, to);

  f_looped = (obj->rtype.pobj_info.anim_flags & AIAF_LOOPING) != 0;
  f_notify = (obj->rtype.pobj_info.anim_flags & AIAF_NOTIFY) != 0;

  if (!f_looped && *anim_frame == to) {
    goto done;
  }

  if (to == from) {
    anim_time = 0.0f;
    goto done;
  }

  if (spc <= 0) {
    *anim_frame = to;
    goto done;
  }

  ASSERT(from <= to);

  if (*anim_frame < from || *anim_frame > to) {
    mprintf(0, "AI/Animation: Correcting for an incorrect frame number\n");
    *anim_frame = from;
  }

  delta = to - from;

  ASSERT(delta >= 0.0f);
  ASSERT(spc > 0.0f);

  if (delta > 0.0f) {
    // step is how much we move this frame
    float max_step = anim_time * ((delta) / spc);

    if (*anim_frame + max_step >= to) {
      anim_time -= anim_time * (to - *anim_frame) / max_step;

      if (f_looped)
        *anim_frame = from;
      else
        *anim_frame = to;

      if (f_notify) {
        //				mprintf(0, "Animation ended\n");
        AINotify(obj, AIN_ANIM_COMPLETE, NULL);
      }

      goto start_loop;
    } else {
      *anim_frame += max_step;
    }
  } else {
    obj->rtype.pobj_info.anim_frame = from;
  }

  if (obj->rtype.pobj_info.anim_frame + 0.001 < from || obj->rtype.pobj_info.anim_frame > to) {
    mprintf(2, "AI ANIM from %0.6f (%0.6f) to %0.6f\n", from, obj->rtype.pobj_info.anim_frame, to);
  }
  if (obj->rtype.pobj_info.anim_frame < from) {
    obj->rtype.pobj_info.anim_frame = from;
  }
  if (obj->rtype.pobj_info.anim_frame > to) {
    obj->rtype.pobj_info.anim_frame = to;
  }

  return;

done:

  if (f_notify) {
    AINotify(obj, AIN_ANIM_COMPLETE, NULL);
  }

  return;
}

#define FRR_MAX_TRIES 15

// MTS: Unused?
int AIGoalGotoRandomRoom() { return -1; }

int AIFindRandomRoom(object *obj, ai_frame *ai_info, goal *goal_ptr, int avoid_room, int min_depth, int max_depth,
                     bool f_check_path, bool f_cur_room_ok, int *depth) {
  int random_room = obj->roomnum;
  int n_tries = 0;
  bool valid = false;
  bool f_use_depth = false;
  int cur_depth;
  int cur_room = obj->roomnum;
  int mine_rooms[MAX_ROOMS];
  int num_mine_rooms = 0;
  int cur_mine = MINE_INDEX(obj->roomnum);
  int i;

  for (i = 0; i <= Highest_room_index; i++) {
    if (Rooms[i].used && !(Rooms[i].flags & RF_EXTERNAL) && cur_mine == MINE_INDEX(i)) {
      mine_rooms[num_mine_rooms++] = i;
      ASSERT(Rooms[mine_rooms[num_mine_rooms - 1]].used);
    }
  }

  if (max_depth >= 0 && min_depth >= 0) {
    f_use_depth = true;
    cur_depth = min_depth + (float)ps_rand() / (float)D3_RAND_MAX * (max_depth - min_depth);
  }

  do {
    random_room = mine_rooms[ps_rand() % num_mine_rooms];
    valid = true;

    if (random_room == avoid_room || ((!f_cur_room_ok) && (random_room == obj->roomnum)) || (!Rooms[random_room].used))
      valid = false;

    if (valid && f_check_path) {
      ASSERT(Rooms[random_room].used);
      ASSERT(Rooms[obj->roomnum].used);
      valid = AIPathAllocPath(obj, ai_info, goal_ptr, &obj->roomnum, &obj->pos, &random_room,
                              &Rooms[random_room].path_pnt, 0.0f, 0, obj->handle);
    }

    n_tries++;
  } while (!valid && n_tries <= FRR_MAX_TRIES && num_mine_rooms > 1);

  if (valid && f_use_depth) {
    while (cur_room != random_room && cur_depth > 0) {
      cur_room = BOA_NEXT_ROOM(cur_room, random_room);
      cur_depth--;
    }

    random_room = cur_room;
  }

  if (!valid) {
    int next_rooms[100];
    int i;
    int pick_list[100];
    int num_pickable = 0;

    int num_next_rooms = AIMakeNextRoomList(obj->roomnum, next_rooms, 100);
    for (i = 0; i < num_next_rooms; i++) {
      if (next_rooms[i] <= Highest_room_index &&
          BOA_DetermineStartRoomPortal(obj->roomnum, NULL, next_rooms[i], NULL) >= 0) {
        pick_list[num_pickable++] = next_rooms[i];
      }
    }

    if (num_pickable) {
      random_room = pick_list[ps_rand() % num_pickable];
      valid = true;
    }

    if (!valid) {
      mprintf(0, "AI:  Wander is generating the same room  :(\n");
      random_room = obj->roomnum;
    }
  }

  ASSERT(random_room >= 0 || random_room <= Highest_room_index + BOA_num_terrain_regions);
  if (random_room > Highest_room_index) {
    // This is a temporary chrishack -- we need to select a random cell in the region
    random_room = ps_rand() % (TERRAIN_WIDTH * TERRAIN_DEPTH);
    random_room |= 0x80000000;
  }

  return random_room;
}

// +/- 8% fluctuation in speed parameters
#define MAX_FLUCTUATION_PERCENT 0.08f

void AIDestroyObj(object *obj) {
  ai_frame *ai_info = obj->ai_info;

#ifdef _DEBUG
  if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
    mprintf(0, "AI Note: In free path\n");
  }
#endif
  AIPathFreePath(&ai_info->path);
}

// Copies AI settings from the object info struct to the object struct
void ObjSetAIInfo(object *objp) {
  int i;

  ai_frame *dest = objp->ai_info;
  ASSERT(dest != NULL);
  if (!(Object_info[objp->id].ai_info))
    return;

  t_ai_info *src = Object_info[objp->id].ai_info;

  dest->ai_class = src->ai_class;
  dest->ai_type = src->ai_type;

  dest->max_velocity = src->max_velocity;
  dest->max_delta_velocity = src->max_delta_velocity;
  dest->max_turn_rate = src->max_turn_rate;
  dest->max_delta_turn_rate = src->max_delta_turn_rate;

  dest->attack_vel_percent = src->attack_vel_percent;
  dest->flee_vel_percent = src->flee_vel_percent;
  dest->dodge_vel_percent = src->dodge_vel_percent;

  dest->circle_distance = src->circle_distance;
  dest->dodge_percent = src->dodge_percent;

  // Note:  Chris is evil.  There should be a symbolic to describe the size of these arrays
  for (i = 0; i < 2; i++) {
    dest->melee_damage[i] = src->melee_damage[i];
    dest->melee_latency[i] = src->melee_latency[i];
  }

  for (i = 0; i < MAX_AI_SOUNDS; i++)
    dest->sound[i] = src->sound[i];

  dest->movement_type = src->movement_type;
  dest->movement_subtype = src->movement_subtype;

  dest->flags = src->flags;
  dest->notify_flags = src->notify_flags;

  dest->fov = src->fov;

  dest->avoid_friends_distance = src->avoid_friends_distance;

  dest->frustration = src->frustration;
  dest->curiousity = src->curiousity;
  dest->life_preservation = src->life_preservation;
  dest->agression = src->agression;

  dest->fire_spread = src->fire_spread;
  dest->night_vision = src->night_vision;
  dest->fog_vision = src->fog_vision;
  dest->lead_accuracy = src->lead_accuracy;
  dest->lead_varience = src->lead_varience;
  dest->fight_team = src->fight_team;
  dest->fight_same = src->fight_same;
  dest->hearing = src->hearing;
  dest->roaming = src->roaming;
  dest->biased_flight_importance = src->biased_flight_importance;
  dest->biased_flight_min = src->biased_flight_min;
  dest->biased_flight_max = src->biased_flight_max;
}

bool AIInit(object *obj, uint8_t ai_class, uint8_t ai_type, uint8_t ai_movement) {
  ai_frame *ai_info = obj->ai_info;
  ASSERT(ai_info);
  ASSERT(obj->control_type == CT_AI && obj->type != OBJ_NONE);

  // Get AI data from the object type info
  ASSERT(IS_GENERIC(obj->type));
  ObjSetAIInfo(obj);

  polyobj_info *p_info = &obj->rtype.pobj_info;
  ai_path_info *path = &ai_info->path;
  int i;
  int anim;

  AIPathInitPath(path);

  bool f_no_scale = (IS_GENERIC(obj->type) && (Object_info[obj->id].flags & OIF_NO_DIFF_SCALE_MOVE)) ||
                    ((ai_info->flags & AIF_TEAM_MASK) == AIF_TEAM_REBEL);

  ai_info->mem_time_till_next_update = 3.0f + (float)ps_rand() / (float)D3_RAND_MAX * 2.0f;
  ai_info->memory.fill(ai_mem{});
  for (i = 0; i < AI_MEM_DEPTH; i++) {
    ai_info->memory[0].shields = obj->shields;
  }

  // In case there is none
  obj->rtype.pobj_info.anim_frame = 0.0;

  ai_info->ai_class = ai_class;
  ai_info->ai_type = ai_type;
  ai_info->movement_type = ai_movement;
  ai_info->next_movement = AI_INVALID_INDEX;
  ai_info->anim_sound_handle = 0;
  ai_info->status_reg = 0;
  ai_info->last_played_sound_index = -1;
  ai_info->weapon_speed = 0.0f;

  ai_info->vec_to_target_perceived = obj->orient.fvec;

  ai_info->last_dodge_dir = Zero_vector;
  ai_info->dodge_till_time = Gametime - 1.0f;

  if (ObjGet(obj->parent_handle)) {
    object *parent = ObjGet(obj->parent_handle);

    if (parent && (parent->type == OBJ_PLAYER || parent->type == OBJ_GHOST)) {
      obj->ai_info->flags &= ~AIF_TEAM_MASK;
      obj->ai_info->flags |= AIF_TEAM_REBEL;
    }
  }

  for (i = 0; i < MAX_AI_SOUNDS; i++) {
    ai_info->last_sound_time[i] = Gametime;
  }

  // Set up the robot to walk if it is applicable
  if (ai_info->movement_type == MC_WALKING) {
    if (Object_info[obj->id].anim[MC_STANDING].elem[AS_ALERT].to)
      ai_info->movement_type = MC_STANDING;

    obj->movement_type = MT_WALKING;
  }

  if ((ObjGet(obj->parent_handle) || Matcen_created) && (Object_info[obj->id].anim[ai_movement].elem[AS_BIRTH].to)) {
    anim = AS_BIRTH;
    ai_info->next_animation_type = AS_IDLE;
    p_info->anim_flags = AIAF_NOTIFY;

    p_info->anim_start_frame = Object_info[obj->id].anim[ai_movement].elem[anim].from;
    p_info->anim_end_frame = Object_info[obj->id].anim[ai_movement].elem[anim].to;
    p_info->anim_time = Object_info[obj->id].anim[ai_movement].elem[anim].spc;
    p_info->anim_frame = Object_info[obj->id].anim[ai_movement].elem[anim].from;
  } else {
    anim = AS_IDLE;

    if (Object_info[obj->id].anim[ai_movement].elem[anim].to == 0.0f)
      anim = AS_ALERT;

    ai_info->next_animation_type = AI_INVALID_INDEX;
    p_info->anim_flags = AIAF_LOOPING;

    // Setup the initial animation state info
    float rand_offset = ps_rand() / ((float)D3_RAND_MAX);
    p_info->anim_start_frame = Object_info[obj->id].anim[ai_movement].elem[anim].from;
    p_info->anim_end_frame = Object_info[obj->id].anim[ai_movement].elem[anim].to;
    p_info->anim_time = Object_info[obj->id].anim[ai_movement].elem[anim].spc;
    p_info->anim_frame = (rand_offset)*Object_info[obj->id].anim[ai_movement].elem[anim].from +
                         (1.0f - rand_offset) * Object_info[obj->id].anim[ai_movement].elem[anim].to;
  }

  ai_info->animation_type = anim;

  if (Object_info[obj->id].anim[ai_movement].elem[anim].anim_sound_index != SOUND_NONE_INDEX) {

    if (!Viewer_object || !Player_object) {
      Player_object = &Objects[0];
      Viewer_object = Player_object;
    }

    // Accounts for sound loading
    if ((obj->handle & HANDLE_COUNT_MASK) != 0) {
      ai_info->last_played_sound_index = Object_info[obj->id].anim[ai_movement].elem[anim].anim_sound_index;
      ai_info->anim_sound_handle = Sound_system.Play3dSound(
          Object_info[obj->id].anim[ai_movement].elem[anim].anim_sound_index, SND_PRIORITY_LOW, obj);
    } else {
      ai_info->last_played_sound_index = -1;
    }
  } else {
    ai_info->last_played_sound_index = -1;
  }

  ai_info->next_melee_time = Gametime;
  ai_info->next_flinch_time = Gametime;
  AISetTarget(obj, OBJECT_HANDLE_NONE);
  ai_info->next_check_see_target_time = Gametime + (float)ps_rand() / (float)D3_RAND_MAX;
  ai_info->last_see_target_time = Gametime - CHECK_VIS_INFREQUENTLY_TIME * 2.0f;
  ai_info->last_hear_target_time = Gametime - CHECK_VIS_INFREQUENTLY_TIME * 2.0f;
  ai_info->last_render_time = -1.0f;
  ai_info->next_target_update_time = Gametime;

  if (ai_info->flags & AIF_FLUCTUATE_SPEED_PROPERTIES) {
    ai_info->max_velocity *=
        1.0f + (((float)ps_rand() - D3_RAND_MAX * 0.5f) / (D3_RAND_MAX * 0.5f)) * MAX_FLUCTUATION_PERCENT;
    ai_info->max_delta_velocity *=
        1.0f + (((float)ps_rand() - D3_RAND_MAX * 0.5f) / (D3_RAND_MAX * 0.5f)) * MAX_FLUCTUATION_PERCENT;
    ai_info->max_turn_rate *=
        1.0f + (((float)ps_rand() - D3_RAND_MAX * 0.5f) / (D3_RAND_MAX * 0.5f)) * MAX_FLUCTUATION_PERCENT;
  }

  ai_info->notify_flags |= AI_NOTIFIES_ALWAYS_ON;

  ai_info->awareness = AWARE_NONE;

  // Apply difficulty settings
  ai_info->dodge_percent *= (f_no_scale) ? 1.0f : Diff_ai_dodge_percent[DIFF_LEVEL];
  ai_info->dodge_vel_percent *= (f_no_scale) ? 1.0f : Diff_ai_dodge_speed[DIFF_LEVEL];
  ai_info->max_velocity *= (f_no_scale || obj->movement_type == MT_WALKING) ? 1.0f : Diff_ai_speed[DIFF_LEVEL];
  ai_info->max_turn_rate *= (f_no_scale || obj->movement_type == MT_WALKING) ? 1.0f : Diff_ai_rotspeed[DIFF_LEVEL];
  ai_info->circle_distance *= (f_no_scale) ? 1.0f : Diff_ai_circle_dist[DIFF_LEVEL];

  ai_info->last_see_target_pos = obj->pos;

  ai_info->vec_to_target_actual = obj->orient.fvec;
  ai_info->vec_to_target_perceived = obj->orient.fvec;

  ai_info->dist_to_target_actual = vm_NormalizeVector(&ai_info->vec_to_target_actual);
  ai_info->dist_to_target_perceived = 10000.0f;

  // Clear out the goals
  GoalInitTypeGoals(obj, ai_info->ai_type);

  if (IS_GUIDEBOT(obj))
    ai_info->flags |= AIF_DODGE;

  return true;
}

// chrishack -- fix the problem with the object being needed for AIInit
void AISetDefault(t_ai_info *ai_info_ptr) {}

void AIInitAll() {
  int i;

  mprintf(0, "Initializing AI systems\n");

  // Initialize the terrain AI system
  ait_Init();

  // Make sure that the buddies are located
  for (i = 0; i < MAX_PLAYERS; i++) {
    Buddy_handle[i] = OBJECT_HANDLE_NONE;
  }

  // Initialize the room AI system

  // Now, initialize each AI object
  for (i = 0; i <= Highest_object_index; i++)
    if (Objects[i].type != OBJ_NONE && Objects[i].control_type == CT_AI) {
      ASSERT(Objects[i].ai_info);
      AIInit(&Objects[i], Objects[i].ai_info->ai_class, Objects[i].ai_info->ai_type, Objects[i].ai_info->movement_type);
    }

  AI_NumRendered = 0;
  AI_NumHostileAlert = 0;

  if (!(Game_mode & GM_MULTI)) {
    int objnum =
        ObjCreate(OBJ_ROBOT, ROBOT_GUIDEBOT, Player_object->roomnum, &Player_object->pos, NULL, Player_object->handle);
    if (objnum > -1) { // DAJ -1FIX
      Buddy_handle[0] = Objects[objnum].handle;
      ObjGhostObject(objnum);
    }
  } else if (Netgame.flags & NF_ALLOWGUIDEBOT) {
    int i;

    for (i = 0; i < MAX_PLAYERS; i++) {
      if (Netgame.local_role == LR_CLIENT) {
        Buddy_handle[i] = OBJECT_HANDLE_NONE;
      } else {
        int parent_handle;

        if (Players[i].objnum < 0 || Players[i].objnum > Highest_object_index ||
            Objects[Players[i].objnum].type == OBJ_NONE) {
          parent_handle = OBJECT_HANDLE_NONE;
        } else {
          parent_handle = Objects[Players[i].objnum].handle;
        }

        // BLACKPYRO
        int objnum =
            ObjCreate(OBJ_ROBOT, ROBOT_GUIDEBOT, Player_object->roomnum, &Player_object->pos, NULL, parent_handle);
        if (objnum > -1) { // DAJ -1FIX
          Buddy_handle[i] = Objects[objnum].handle;
          ObjGhostObject(objnum);
        }
      }
    }
  }

  mprintf(0, "Done Initializing AI systems\n");
}

void AICheckTargetVis(object *obj) {
  ai_frame *ai_info = obj->ai_info;
  object *target = ObjGet(ai_info->target_handle);

#ifdef _DEBUG
  if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
    mprintf(0, "AI Note: Vis 1\n");
  }
#endif

#ifdef _DEBUG
  if (!Game_do_ai_vis) {
    ai_info->status_reg &= ~AISR_SEES_GOAL;
    ai_info->last_see_target_pos = obj->pos;
    return;
  }
#endif

  if (target == NULL) {
    ai_info->status_reg &= ~AISR_SEES_GOAL;
    ai_info->last_see_target_pos = obj->pos;
    return;
  }

#ifdef _DEBUG
  if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
    mprintf(0, "AI Note: Vis 2\n");
  }
#endif

  if (!BOA_IsVisible(obj->roomnum, target->roomnum)) {
    ai_info->status_reg &= ~AISR_SEES_GOAL;
    return;
  }

#ifdef _DEBUG
  if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
    mprintf(0, "AI Note: Vis 3\n");
  }
#endif

  vector pos;
  AIDetermineAimPoint(obj, target, &pos);
  ai_info->vec_to_target_actual = pos - obj->pos;
  ai_info->dist_to_target_actual = vm_NormalizeVector(&ai_info->vec_to_target_actual);
  ai_info->dist_to_target_actual -= (obj->size + target->size);
  if (ai_info->dist_to_target_actual < 0.0f)
    ai_info->dist_to_target_actual = 0.0f;

  vector fov_vec;
  AIDetermineFovVec(obj, &fov_vec);

  if (ai_info->vec_to_target_actual * fov_vec < ai_info->fov) {
    ai_info->status_reg &= ~AISR_SEES_GOAL;
    return;
  }

#ifdef _DEBUG
  if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
    mprintf(0, "AI Note: Vis 4\n");
  }
#endif

  if (ai_info->dist_to_target_actual > MAX_TRACK_TARGET_DIST * Diff_ai_vis_dist[DIFF_LEVEL] &&
      (!ObjGet(ai_info->target_handle) || (obj->roomnum != ObjGet(ai_info->target_handle)->roomnum))) {
    ai_info->status_reg &= ~AISR_SEES_GOAL;
    return;
  }

#ifdef _DEBUG
  if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
    mprintf(0, "AI Note: Vis 5\n");
  }
#endif

  if (ai_info->awareness == AWARE_NONE && (target->roomnum != obj->roomnum) &&
      ai_info->dist_to_target_actual > MAX_SEE_TARGET_DIST * Diff_ai_vis_dist[DIFF_LEVEL]) {
    ai_info->status_reg &= ~AISR_SEES_GOAL;
    return;
  }

#ifdef _DEBUG
  if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
    mprintf(0, "AI Note: Vis 6\n");
  }
#endif

  if ((ai_info->dist_to_target_actual > MAX_SEE_TARGET_DIST * Diff_ai_vis_dist[DIFF_LEVEL] &&
       ai_info->awareness <= AWARE_BARELY && (target->roomnum != obj->roomnum)) ||
      (target->type == OBJ_PLAYER && (Players[target->id].flags & (PLAYER_FLAGS_DEAD | PLAYER_FLAGS_DYING))) ||
      target->type == OBJ_GHOST || !AIDetermineObjVisLevel(obj, target)) {
    //.		mprintf(0, "No check vis\n");
    ai_info->status_reg &= ~AISR_SEES_GOAL;
    return;
  }

#ifdef _DEBUG
  if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
    mprintf(0, "AI Note: Vis 7\n");
  }
#endif

  // Can I see the target?
  if (Gametime - ai_info->last_see_target_time > MIN_VIS_RECENT_CHECK_INTERVAL) {
    if (Gametime >= ai_info->next_check_see_target_time) {
      //			float dist;
      fvi_info hit_info;
      fvi_query fq;
      int fate;

      // Project a ray and see if target is around. -- We can use a quick room check to see if we should even do it.  :)
      // --chrishack (do this later when room structure is in the game)
      // if we are in the same room, see see the target
      // Do FVI_stuff (maybe just a room connection check)

      // shoot a ray from the light position to the current vertex
      fq.p0 = &obj->pos;
      fq.p1 = &target->pos;
      fq.startroom = obj->roomnum;

      fq.rad = 0.0f;
      fq.flags = FQ_CHECK_OBJS | FQ_IGNORE_POWERUPS | FQ_IGNORE_WEAPONS | FQ_NO_RELINK /* | FQ_IGNORE_MOVING_OBJECTS*/;
      if (ai_info->agression > .7f) {
        fq.flags |= FQ_IGNORE_MOVING_OBJECTS;
      }

      fq.thisobjnum = -1;

      int ignore_obj_list[100];
      ignore_obj_list[0] = OBJNUM(obj);
      int num_ignored = 1;
      int i;

      // CHRISHACK - ONLY IGNORES FIRST LEVEL OF CHILDREN - DO RECERSIVE
      for (i = 0; i < Poly_models[obj->rtype.pobj_info.model_num].n_attach; i++) {
        object *child;

        if ((child = ObjGet(obj->attach_children[i])) != NULL && num_ignored < 99) {
          ignore_obj_list[num_ignored++] = OBJNUM(child);
        }
      }

      ignore_obj_list[num_ignored] = -1;
      fq.ignore_obj_list = ignore_obj_list;

      fate = fvi_FindIntersection(&fq, &hit_info);

#ifdef _DEBUG
      if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
        mprintf(0, "AI Note: Vis 8\n");
      }
#endif

      if (((fate == HIT_OBJECT || fate == HIT_SPHERE_2_POLY_OBJECT) && hit_info.hit_object[0] == OBJNUM(target)) ||
          (fate == HIT_NONE)) {
        ai_info->status_reg |= AISR_SEES_GOAL; // chrishack -- need to do this stuff correctly
        // if(ai_info->highest_vis > )  chrishack -- need to do this stuff

        AINotify(obj, AIN_SEE_TARGET, target);

#ifdef _DEBUG
        if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
          mprintf(0, "AI Note: Vis SEE TARGET\n");
        }
#endif
      }

      if ((ai_info->status_reg & AISR_SEES_GOAL) ||
          Gametime - ai_info->last_see_target_time < CHECK_VIS_INFREQUENTLY_TIME)
        ai_info->next_check_see_target_time =
            Gametime + .9 * MIN_VIS_CHECK_INTERVAL + .2 * MIN_VIS_CHECK_INTERVAL * ((float)ps_rand() / (float)D3_RAND_MAX);
      else
        ai_info->next_check_see_target_time =
            Gametime + .9 * CHECK_VIS_INFREQUENTLY_INTERVAL +
            .2 * CHECK_VIS_INFREQUENTLY_INTERVAL * ((float)ps_rand() / (float)D3_RAND_MAX);
    }
  }

  if ((ai_info->status_reg & AISR_SEES_GOAL)) {
    ai_info->vec_to_target_perceived = ai_info->vec_to_target_actual;
    ai_info->dist_to_target_perceived = ai_info->dist_to_target_actual;

    // Assumes the the AI and the target are on the same XZ plane
    /*		if(ai_info->flags & AIF_XZ_DIST)
                    {
                            vector xz;

                            xz = ai_info->vec_to_target_perceived * ai_info->dist_to_target_perceived;
                            xz.y = 0.0f; // chrishack - E3 - it this a good way to do this?

    //			vm_NormalizeVector(&ai_info->vec_to_target_perceived);
                            ai_info->dist_to_target_perceived = vm_GetMagnitude(&xz);
                    }*/
  }
}

bool AIStatusCircleFrame(object *obj, object *g_obj, float dist, float c_dist, int *status_reg) {
  if ((*status_reg) & AISR_CIRCLE_DIST) {
    if (dist > c_dist * 1.5f || (obj->ai_info->awareness <= AWARE_BARELY && !(obj->ai_info->flags & AIF_PERSISTANT))) {
      (*status_reg) &= ~AISR_CIRCLE_DIST;
      return false;
    } else {
      return true;
    }
  } else if (dist <= c_dist + .1f &&
             (obj->ai_info->awareness >= AWARE_BARELY || (obj->ai_info->flags & AIF_PERSISTANT))) {
    (*status_reg) |= AISR_CIRCLE_DIST;

    if (g_obj) {
      AINotify(obj, AIN_NEAR_TARGET, (void *)g_obj);
    }

    return true;
  } else {
    return false;
  }
}

// MTS: Unused?
bool ai_target_need_path(object *obj) { return true; }

// MTS: Unused?
bool ai_move_need_path(object *obj, vector *pos, int roomnum) {
  if (obj->roomnum == roomnum) {
    return false;
  }

  return true;
}

void ai_update_registers(object *obj) {
  ai_frame *ai_info = obj->ai_info;

  if (ObjGet(ai_info->target_handle)) {
    AIStatusCircleFrame(obj, ObjGet(ai_info->target_handle), ai_info->dist_to_target_perceived,
                        ai_info->circle_distance, &ai_info->status_reg);
  } else {
    ai_info->status_reg &= ~AISR_CIRCLE_DIST;
  }

  ai_info->status_reg &= ~AISR_MELEE;
}

bool AiGoalAvoid(vector *adir, object *obj, object *a_obj, float dist) {
  float full_dist = dist;
  vector a_vel;

  if (obj->movement_type != MT_PHYSICS && obj->movement_type != MT_WALKING)
    return false;

  if (a_obj->movement_type == MT_PHYSICS || a_obj->movement_type == MT_WALKING)
    a_vel = a_obj->mtype.phys_info.velocity;
  else
    a_vel = Zero_vector;

  vector to_avoid = a_obj->pos - obj->pos;
  vector mdir;
  mdir = obj->mtype.phys_info.velocity - a_vel;

  if (fabsf(mdir.x) < 0.1f && fabsf(mdir.y) < 0.1f && fabsf(mdir.z) < 0.1f) {
    *adir = -to_avoid;
    vm_NormalizeVector(adir);

    return true;
  }

  vm_NormalizeVector(&mdir);
  float temp = mdir * to_avoid;

  if (temp <= 0.0f) {
    *adir = -to_avoid;
    vm_NormalizeVector(adir);

    return true;
  }

  vector vtemp = -(to_avoid - temp * mdir);

  //	float cdist = vm_NormalizeVector(&vtemp);
  //	if(cdist >= full_dist)
  //		return false;

  vector apnt = a_obj->pos + full_dist * vtemp;

  *adir = apnt - obj->pos;
  vm_NormalizeVector(adir);

  return true;
}

static inline bool IsTargetLocal(object *obj, object *target) {
  int target_room = target->roomnum;
  int cur_room = obj->roomnum;
  int i;

  // If they are in the same room
  if ((target_room = obj->roomnum)) {
    return true;
  }

  // If the object is outside
  if (OBJECT_OUTSIDE(obj)) {
    return false;
  }

  // If they are in directly adjacent rooms
  for (i = 0; i < Rooms[cur_room].num_portals; i++) {
    if (Rooms[cur_room].portals[i].croom == target_room) {
      return true;
    }
  }

  return false;
}

#define AVOID_PLAYER_MAX_SCALAR 3.0f
#define AVOID_PLAYER_MIN_SCALAR 2.0f

#define ALIGNMENT_OPTI_DIST 16.0f
#define MAX_ALIGNMENT_DIST 6.0f

#define COHESION_OPTI1_DIST 90.0f
#define COHESION_OPTI2_DIST 90.0f
#define COHESION_FALL_OFF 110.0f

// MTS: commented out/returns a bool instead of a float
float AIGoalIsEnabledForDist(goal *goal, float dist) {
  return true; // chrishack -- test code -- temp
}

void AIGoalDoRepulse(object *obj, float dist, vector *dir, goal *goal, vector *mdir) {
  float influence = 2.0f; // chrishack - temp - test code

  if (/*scale = AIGoalIsEnabledForDist(goal, dist)*/ 1) // chrishack - temp - test code - works like an enabler  What
                                                        // about AIDetermineScale????
  {
    if (dist <= 12.0f) // chrishack - temp - test code
    {
      float scale;

      if (dist < 9.0f)
        scale = 1.0f;
      else
        scale = 1.0f - (dist - 9.0f) / 3.0;

      *mdir += (*dir * -scale) * influence;
    }
  }
}

void AIGoalDoCohesion(object *obj, object *g_obj, float dist, goal *goal, vector *mdir) {
  float influence = 2.0f; // chrishack - temp - test code

  if (/*scale = AIGoalIsEnabledForDist(goal, dist)*/ 1) // chrishack - temp - test code - works like an enabler  What
                                                        // about AIDetermineScale????
  {
    if (dist >= COHESION_OPTI1_DIST - COHESION_FALL_OFF && dist <= COHESION_OPTI2_DIST + COHESION_FALL_OFF) {
      vector cohesion_pnt;
      float scale;

      if (dist < COHESION_OPTI1_DIST)
        scale = 1.0f - (COHESION_OPTI1_DIST - dist) / COHESION_FALL_OFF;
      else if (dist <= COHESION_OPTI2_DIST)
        scale = 1.0f;
      else
        scale = 1.0f - (dist - COHESION_OPTI2_DIST) / COHESION_FALL_OFF;

      AIDetermineAimPoint(obj, g_obj, &cohesion_pnt, obj->ai_info->max_velocity);

      vector cur_cohesion_dir = cohesion_pnt - obj->pos;
      vm_NormalizeVector(&cur_cohesion_dir);
      *mdir += (cur_cohesion_dir * scale) * influence;
    }
  }
}

void AIGoalDoAlignment(object *obj, float dist, vector *fvec, goal *goal, vector *mdir) {
  float influence = 3.0f; // chrishack - temp - test code

  if (/*scale = AIGoalIsEnabledForDist(goal, dist)*/ 1) // chrishack - temp - test code - works like an enabler  What
                                                        // about AIDetermineScale????
  {
    float align_dist = fabs(dist - ALIGNMENT_OPTI_DIST);
    if (MAX_ALIGNMENT_DIST >= align_dist) {
      float scale = 1.0f - (align_dist / MAX_ALIGNMENT_DIST);
      *mdir += (*fvec * scale) * influence;
    }
  }
}

void AIDoTrackFrame(object *obj) {
  ai_frame *ai_info = obj->ai_info;
  float track_distance;

  AI_FriendNumNear = 0;
  AI_EnemyNumNear = 0;

  if (ai_info->ai_type == AIT_BIRD_FLOCK1 ||
      ai_info->flags & (AIF_TRACK_CLOSEST_2_FRIENDS | AIF_TRACK_CLOSEST_2_ENEMIES)) {

    if (ai_info->ai_type == AIT_BIRD_FLOCK1)
      track_distance = 100.0f;
    else
      track_distance = GoalDetermineTrackDist(obj);

    if (track_distance > 0.0f) {
      int16_t near_objs[10];
      int num_near = fvi_QuickDistObjectList(&obj->pos, obj->roomnum, ai_info->avoid_friends_distance + track_distance,
                                             near_objs, 10, false, true, false, true);
      float dist;
      vector to;

      AI_EnemyDist[0] = AI_EnemyDist[1] = 9999999.0f;
      AI_FriendDist[0] = AI_FriendDist[1] = 9999999.0f;

      for (int xxx = 0; xxx < num_near; xxx++) {
        object *g_obj = &Objects[near_objs[xxx]];

        if (g_obj->type == OBJ_POWERUP || (obj == g_obj) || ObjectsAreRelated(OBJNUM(obj), near_objs[xxx]))
          continue;

        int *cur_num_near;
        object **cur_obj;
        float *cur_dist;
        vector *cur_dir;

        if ((ai_info->flags & AIF_TRACK_CLOSEST_2_ENEMIES) && AIObjEnemy(obj, g_obj)) {
          cur_num_near = &AI_EnemyNumNear;
          cur_obj = AI_EnemyObj;
          cur_dist = AI_EnemyDist;
          cur_dir = AI_EnemyDir;
        } else if ((ai_info->flags & AIF_TRACK_CLOSEST_2_FRIENDS) && AIObjFriend(obj, g_obj)) {
          cur_num_near = &AI_FriendNumNear;
          cur_obj = AI_FriendObj;
          cur_dist = AI_FriendDist;
          cur_dir = AI_FriendDir;
        } else
          continue;

        to = g_obj->pos - obj->pos;
        dist = vm_NormalizeVector(&to);

        dist -= (obj->size + g_obj->size);
        if (dist < 0.0f)
          dist = 0.0f;

        vector fov_vec;
        AIDetermineFovVec(obj, &fov_vec);

        if (to * fov_vec < ai_info->fov)
          continue;

        if (cur_dist[0] > dist) {
          cur_dist[1] = cur_dist[0];
          cur_obj[1] = cur_obj[0];
          cur_dir[1] = cur_dir[0];

          cur_dist[0] = dist;
          cur_obj[0] = g_obj;
          cur_dir[0] = to;

          (*cur_num_near)++;
        } else if (cur_dist[1] > dist) {
          cur_dist[1] = dist;
          cur_obj[1] = g_obj;
          cur_dir[1] = to;

          (*cur_num_near)++;
        }

        if (*cur_num_near > 2)
          *cur_num_near = 2;
      }
    }
  }
}

// MTS: unused?
float AIDetermineGoalInfluence(object *obj, goal *goal) {
  float influence = goal->influence;
  int g_index = goal - obj->ai_info->goals;

  if (goal->flags & GF_SCRIPTED_INFLUENCE) {
    AINotify(obj, AIN_SCRIPTED_INFLUENCE, &g_index);
    influence = goal->influence;
  } else if (goal->flags & GF_RAMPED_INFLUENCE) {
    float scale;
    const float dist = goal->dist_to_goal; // chrishack -- dist to goal must be properly updated for TRACK goals

    if (dist < goal->ramp_influence_dists[1]) {
      float delta = dist - goal->ramp_influence_dists[0];
      float width = goal->ramp_influence_dists[1] - goal->ramp_influence_dists[0];

      if (width > 0.0f)
        scale = delta / width;
      else
        scale = 0.0f;
    } else if (dist <= goal->ramp_influence_dists[2]) {
      scale = 1.0f;
    } else {
      float delta = goal->ramp_influence_dists[3] - dist;
      float width = goal->ramp_influence_dists[3] - goal->ramp_influence_dists[2];

      if (width > 0.0f)
        scale = delta / width;
      else
        scale = 0.0f;
    }

    influence *= scale;
  }

  if ((goal->flags & GF_MIN_MAX_INFLUENCE) && influence < goal->min_influence) {
    influence = goal->min_influence;
  }

  return influence;
}

void AIDoOrientVelocity(object *obj) {
  ai_frame *ai_info = obj->ai_info;

  vector dir = obj->mtype.phys_info.velocity;
  float mag = vm_NormalizeVector(&dir);

  if (mag > 0.1f) {
    AITurnTowardsDir(obj, &dir, ai_info->max_turn_rate);
  }
}

void AIDoOrientDefault(object *obj) {
  ai_frame *ai_info = obj->ai_info;

  if ((obj->movement_type != MT_WALKING && obj->movement_type != MT_PHYSICS) || !(ai_info)) {
    return;
  }

  // The aware barely stuff can be improved by using emotional sliders to determine if the robot will
  // 'lose track' of its target -- chrishack -- also use last see target time with the agression slider
  if ((ai_info->flags & AIF_ORIENT_TO_VEL) || (ai_info->awareness <= AWARE_BARELY && ai_info->agression < 0.4f) ||
      !ObjGet(ai_info->target_handle)) {
    AIDoOrientVelocity(obj);
  } else {
    vector to = ai_info->last_see_target_pos - obj->pos;
    float dist = vm_NormalizeVector(&to);

    if (dist > .1f)
      AITurnTowardsDir(obj, &to, ai_info->max_turn_rate);
  }
}

void AIDoOrient(object *obj, int g_index) {
  ai_frame *ai_info = obj->ai_info;
  goal *goal_ptr = &ai_info->goals[g_index];

  if ((obj->movement_type != MT_WALKING && obj->movement_type != MT_PHYSICS) || !(ai_info)) {
    return;
  }

  if ((g_index >= 0) && ISORIENTGOAL(&ai_info->goals[g_index])) {
    object *g_obj = NULL;

    if (goal_ptr->flags & GF_ORIENT_FOR_ATTACH) {
      Int3(); // chrishack -- not done
    } else if (goal_ptr->flags & GF_ORIENT_TARGET) {
    target_goal:

      g_obj = ObjGet(ai_info->target_handle);
      if (g_obj) {
        vector to = ai_info->last_see_target_pos - obj->pos;
        float dist = vm_NormalizeVector(&to);

        if (dist > .1f)
          AITurnTowardsDir(obj, &to, ai_info->max_turn_rate);
      } else {
        AIDoOrientVelocity(obj);
      }
    } else if (OBJGOAL(goal_ptr) && (goal_ptr->flags & GF_ORIENT_GOAL_OBJ)) {
      object *t_obj = ObjGet(ai_info->target_handle);
      g_obj = ObjGet(goal_ptr->g_info.handle);

      if (g_obj && (g_obj == t_obj))
        goto target_goal;

      if (g_obj) {
        vector to = g_obj->pos - obj->pos;
        float dist = vm_NormalizeVector(&to);

        if (dist > .1f)
          AITurnTowardsDir(obj, &to, ai_info->max_turn_rate);
      } else {
        AIDoOrientVelocity(obj);
      }
    } else if (goal_ptr->flags & GF_ORIENT_VELOCITY) {
      AIDoOrientVelocity(obj);
    } else if (goal_ptr->flags & GF_ORIENT_SCRIPTED) {
      AINotify(obj, AIN_SCRIPTED_ORIENT, &g_index);
    } else if (goal_ptr->flags & GF_ORIENT_PATH_NODE) {
      vector uvec = obj->orient.uvec;
      vector fvec = obj->orient.fvec;

      ai_path_info *aip = &obj->ai_info->path;

      int n = aip->cur_node;
      int p = aip->cur_path;

      int p_id = aip->path_id[p];

      bool f_reverse = (goal_ptr->flags & GF_PATH_MOVE_REVERSE_DIR) != 0;

      if (aip->path_type[p] == AIP_STATIC) {
        game_path *gp = &GamePaths[p_id];
        vector cur_pos;
        AIPathGetCurrentNodePos(aip, &cur_pos);

        if ((f_reverse) && (!AIPathAtEnd(aip))) {
          vector next_pos;
          AIPathGetNextNodePos(aip, &next_pos, NULL);

          vector proj = obj->pos - next_pos;
          vector line = cur_pos - next_pos;
          float line_len = vm_NormalizeVector(&line);
          float proj_len = proj * line;

          if (proj_len > 0.0) {
            if (proj_len > line_len)
              return; // We should have updated nodes

            float scale1 = proj_len / line_len;
            float scale2 = 1.0f - scale1;

            fvec = (scale1 * gp->pathnodes[n].fvec + scale2 * gp->pathnodes[n + 1].fvec);
            uvec = (scale1 * gp->pathnodes[n].uvec + scale2 * gp->pathnodes[n + 1].uvec);
          }
        } else if ((!f_reverse) && (!AIPathAtStart(aip))) {
          vector prev_pos;
          AIPathGetPrevNodePos(aip, &prev_pos, NULL);

          vector proj = obj->pos - prev_pos;
          vector line = cur_pos - prev_pos;
          float line_len = vm_NormalizeVector(&line);
          float proj_len = proj * line;

          if (proj_len > 0.0) {
            if (proj_len > line_len)
              return; // We should have updated nodes

            float scale1 = proj_len / line_len;
            float scale2 = 1.0f - scale1;

            fvec = (scale1 * gp->pathnodes[n].fvec + scale2 * gp->pathnodes[n - 1].fvec);
            uvec = (scale1 * gp->pathnodes[n].uvec + scale2 * gp->pathnodes[n - 1].uvec);
          }
        }

        matrix orient;
        vm_VectorToMatrix(&orient, &fvec, &uvec, NULL);

        AITurnTowardsMatrix(obj, ai_info->max_turn_rate, &orient);
      }
    } else if (goal_ptr->flags & GF_ORIENT_SET_FVEC_UVEC) {
      matrix orient;
      vm_VectorToMatrix(&orient, &goal_ptr->set_fvec, &goal_ptr->set_uvec, NULL);

      AITurnTowardsMatrix(obj, ai_info->max_turn_rate, &orient);
    } else if (goal_ptr->flags & GF_ORIENT_SET_FVEC) {
      AITurnTowardsDir(obj, &goal_ptr->set_fvec, ai_info->max_turn_rate);
    } else {
      AIDoOrientDefault(obj);
    }
  } else {
    AIDoOrientDefault(obj);
  }
}

void AIDetermineSpeed(object *obj, int flags, float *speed) {
  float n_speed = 1.0f;

  switch (flags & GF_SPEED_MASK) {
  case GF_SPEED_ATTACK:
    n_speed = obj->ai_info->attack_vel_percent;
    break;
  case GF_SPEED_DODGE:
    n_speed = obj->ai_info->dodge_vel_percent;
    break;
  case GF_SPEED_FLEE:
    n_speed = obj->ai_info->flee_vel_percent;
    break;
  }

  if (n_speed > *speed) {
    *speed = n_speed;
  }
}

void ai_move(object *obj) {
  ai_frame *ai_info = obj->ai_info;
  int i;
  bool f_dodge = false; // Are there any dodge goals
  bool f_avoid = false; // Are there any avoid goals
  int highest_influence_goal = -1;
  float highest_influence = 0.0f;
  float highest_speed = 0.0f;
  bool f_turned = true;
  bool f_goal_found = false;

  // Post project GB Hacks to make him more combat friendly...
  if (IS_GUIDEBOT(obj)) {
    if (ai_info->flags & AIF_GB_MIMIC_PLAYER_FIRING_HACK)
      ai_info->flags &= ~AIF_DODGE;
    else
      ai_info->flags |= AIF_DODGE;
  }
  // int num_objects;
  // object *g_objs[5]; // 1 target + 2 enemies + 2 freinds

  object *targetptr = ObjGet(ai_info->target_handle); // The target of this AI
  ai_info->movement_dir = Zero_vector;

  // Hacked flocking code
  if (ai_info->ai_type == AIT_BIRD_FLOCK1) {
    vector composite_dir = Zero_vector;

    for (int temp = 0; temp < AI_FriendNumNear; temp++) {
      object *g_obj = AI_FriendObj[temp];

      ASSERT(g_obj->type != OBJ_WEAPON);
      ASSERT(g_obj != obj);

      AIGoalDoRepulse(obj, AI_FriendDist[temp], &AI_FriendDir[temp], NULL, &composite_dir);
      AIGoalDoAlignment(obj, AI_FriendDist[temp], &g_obj->orient.fvec, NULL, &composite_dir);
      AIGoalDoCohesion(obj, g_obj, AI_FriendDist[temp], NULL, &composite_dir);
      f_goal_found = true;
    }

    // Facing code
    if (composite_dir == Zero_vector)
      composite_dir = obj->orient.fvec;

    // FLOCK HEIGHT CODE
    if (ROOMNUM_OUTSIDE(obj->roomnum) && (ai_info->flags & AIF_BIASED_FLIGHT_HEIGHT)) {
      composite_dir.y *= .5f;

      float delta = obj->pos.y - GetTerrainGroundPoint(&obj->pos) - obj->size;
      if (delta < ai_info->biased_flight_min) {
        if (composite_dir.y < 0.0)
          composite_dir.y *= .5f;
        else
          composite_dir.y *= 4.0f;
      } else if (delta > ai_info->biased_flight_max) {
        if (composite_dir.y < 0.0)
          composite_dir.y *= 4.0f;
        else
          composite_dir.y *= 0.5f;
      }

      float max_fly_upward_height = ai_info->biased_flight_min * ai_info->biased_flight_importance;
      if (delta < max_fly_upward_height) {
        composite_dir.y += (1.0f - (delta / max_fly_upward_height)) * ai_info->biased_flight_importance;
      }
    }

    vm_NormalizeVector(&composite_dir);

    AIMoveTowardsDir(obj, &composite_dir, 1.0f);
    AITurnTowardsDir(obj, &composite_dir, ai_info->max_turn_rate);
    return;
  }

  // Stop objects that have not been active lately
  if (!(ai_info->flags & AIF_PERSISTANT) && Gametime - ai_info->last_see_target_time > CHECK_VIS_INFREQUENTLY_TIME &&
      Gametime - ai_info->last_hear_target_time > CHECK_VIS_INFREQUENTLY_TIME && ai_info->awareness == AWARE_NONE) {
    obj->mtype.phys_info.velocity = Zero_vector;
    obj->mtype.phys_info.rotvel = Zero_vector;
  } else {
    // Determine movement stuff
    if (obj->movement_type == MT_PHYSICS || obj->movement_type == MT_WALKING) {
      if (targetptr && IsTargetLocal(obj, targetptr) || (ai_info->awareness >= AWARE_BARELY) ||
          (ai_info->flags & AIF_PERSISTANT)) {
        for (i = NUM_ACTIVATION_LEVELS; i < MAX_GOALS; i++) {
          if (ai_info->goals[i].used) {
            if (GoalIsGoalEnabled(obj, i)) {
              if (ai_info->goals[i].type == AIG_DODGE_OBJ) {
                f_goal_found = true;
                if (goal_do_dodge(obj, i)) {
                  f_dodge = true;
                  AIDetermineSpeed(obj, ai_info->goals[i].flags, &highest_speed);

#ifdef _DEBUG
                  if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
                    mprintf(0, "AI Note: Dodging\n");
                  }
#endif
                }
              } else if (ai_info->goals[i].type == AIG_MELEE_TARGET) {
                f_goal_found = true;
                AiMelee(obj);
                AIDetermineSpeed(obj, ai_info->goals[i].flags, &highest_speed);

#ifdef _DEBUG
                if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
                  mprintf(0, "AI Note: Melee\n");
                }
#endif
              } else if (ai_info->goals[i].type == AIG_GET_AROUND_OBJ) {
                f_goal_found = true;

                goal *cur_goal = &ai_info->goals[i];
                object *g_obj = ObjGet(cur_goal->g_info.handle);
                float dist = cur_goal->circle_distance;

                vector adir;

                if (!g_obj || (g_obj == obj) || ObjectsAreRelated(OBJNUM(obj), OBJNUM(g_obj)))
                  continue;

                float cur_dist = vm_VectorDistance(&obj->pos, &g_obj->pos) - obj->size - g_obj->size;
                if (cur_dist < 0.0)
                  cur_dist = 0.0f;

                if (cur_dist > dist)
                  continue;

                // Scale the life perservation too (if enemy DAMN GOOD IDEA - expand AVOID SIZE too)   -- chrishack
                // Linear scale by distance
                float scale = cur_goal->influence * ((dist - cur_dist) / dist);

                if (AiGoalAvoid(&adir, obj, g_obj, dist)) {
#ifdef _DEBUG
                  if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
                    mprintf(0, "AI Note: Avoiding object\n");
                  }
#endif

                  ai_info->movement_dir += (adir * scale);
                  f_avoid = true;
                  AIDetermineSpeed(obj, ai_info->goals[i].flags, &highest_speed);
                }
              }
            }
          }
        }

        if (ai_info->flags & AIF_AUTO_AVOID_FRIENDS) {
          object *g_obj;
          vector adir;

          f_goal_found = true;

          int16_t near_objs[10];

          float avoid_dist;

          avoid_dist = ai_info->avoid_friends_distance;

          // We avoid friends more when we are in close proximity of our target
          if (AIObjEnemy(obj, ObjGet(ai_info->target_handle)) && (ai_info->status_reg & AISR_CIRCLE_DIST))
            avoid_dist *= 2.3f;

          int num_near = fvi_QuickDistObjectList(&obj->pos, obj->roomnum, ai_info->avoid_friends_distance + obj->size,
                                                 near_objs, 10, false, true);

          for (int temp = 0; temp < num_near; temp++) {
            g_obj = &Objects[near_objs[temp]];

            if (g_obj->type == OBJ_POWERUP || (g_obj == obj) || ObjectsAreRelated(OBJNUM(obj), near_objs[temp]))
              continue;

            if (!AIObjFriend(obj, g_obj))
              continue;

            float cur_dist = vm_VectorDistance(&obj->pos, &g_obj->pos) - obj->size - g_obj->size;
            if (cur_dist < 0.0)
              cur_dist = 0.0f;

            if (cur_dist > ai_info->avoid_friends_distance)
              continue;

            if (AiGoalAvoid(&adir, obj, g_obj, ai_info->avoid_friends_distance)) {
              float scale = 1.0f - cur_dist / ai_info->avoid_friends_distance;
              if (scale < 0.01f)
                scale = 0.01f;

              ai_info->movement_dir += (adir * scale);
              f_avoid = true;
              AIDetermineSpeed(obj, GF_SPEED_NORMAL, &highest_speed);

#ifdef _DEBUG
              if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
                mprintf(0, "AI Note: Auto avoid friends.\n");
              }
#endif
            }
          }
        }

        if (ai_info->flags & AIF_AVOID_WALLS) {
          if (goal_do_avoid_walls(obj, &ai_info->movement_dir)) {
            f_avoid = true;
            AIDetermineSpeed(obj, GF_SPEED_NORMAL, &highest_speed);

#ifdef _DEBUG
            if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
              mprintf(0, "AI Note: Avoiding walls\n");
            }
#endif
          }
        }

        goal *cur_goal = GoalGetCurrentGoal(obj);
        vector goal_mdir;
        bool goal_f_moved = false;
        bool goal_mset = false;

        if (cur_goal) {
          f_goal_found = true;
          highest_influence_goal = cur_goal - ai_info->goals;
          f_turned = false;
          AIDetermineSpeed(obj, cur_goal->flags, &highest_speed);

          switch (cur_goal->type) {
          case AIG_SCRIPTED: {
            int g_index = cur_goal - ai_info->goals;
            AINotify(obj, AIN_SCRIPTED_GOAL, &g_index); // Assume that it modifies the movement vec

            int goal_mscale = vm_NormalizeVector(&ai_info->movement_dir);
            goal_mdir = ai_info->movement_dir;

            if (goal_mscale > highest_speed) {
              highest_speed = goal_mscale;
            }

            goal_mset = true;
          } break;

          case AIG_GUARD_AREA: // Chrishack -- this goal could probably be removed
          {
            if (!(cur_goal->status_reg & AISR_CIRCLE_DIST)) {
              if (cur_goal->g_info.roomnum != obj->roomnum) {
                cur_goal->g_info.roomnum = obj->roomnum;
                cur_goal->g_info.pos = obj->pos;
              }

              AIMoveTowardsPosition(obj, &cur_goal->g_info.pos, 1.0f, false, &goal_mdir, &goal_f_moved);
              goal_mset = true;
            }
          } break;

          case AIG_GET_TO_OBJ:
          case AIG_GET_TO_POS:
          case AIG_WANDER_AROUND:
          case AIG_FOLLOW_PATH:
          case AIG_PLACE_OBJ_ON_OBJ:
          case AIG_ATTACH_TO_OBJ: {
            if ((cur_goal->type == AIG_ATTACH_TO_OBJ || cur_goal->type == AIG_PLACE_OBJ_ON_OBJ) &&
                (cur_goal->status_reg & AISR_CIRCLE_DIST)) {
              object *g_obj = ObjGet(cur_goal->g_info.handle);
              object *child_obj = NULL;

              if (cur_goal->type == AIG_PLACE_OBJ_ON_OBJ) {
                child_obj = ObjGet(obj->attach_children[0]);

                if (child_obj == NULL) {
                  cur_goal->flags &= ~(GF_NONFLUSHABLE | GF_KEEP_AT_COMPLETION);
                  GoalClearGoal(obj, cur_goal, AIN_GOAL_INVALID);
                  return;
                }
              }

              vector pos;
              matrix orient;
              char p_ap = cur_goal->g_info.attach_info.parent_ap;
              char c_ap = cur_goal->g_info.attach_info.child_ap;
              float rad = cur_goal->g_info.attach_info.rad;

              // Investigate a better means of doing this...
              if (!(obj->mtype.phys_info.flags & PF_NO_ROBOT_COLLISIONS)) {
                obj->mtype.phys_info.flags |= PF_NO_ROBOT_COLLISIONS;
                cur_goal->g_info.attach_info.flags |= GAF_TEMP_CLEAR_ROBOT_COLLISIONS;
              }
              if (!(obj->mtype.phys_info.flags & PF_POINT_COLLIDE_WALLS)) {
                obj->mtype.phys_info.flags |= PF_POINT_COLLIDE_WALLS;
                cur_goal->g_info.attach_info.flags |= GAF_TEMP_POINT_COLLIDE_WALLS;
              }
              if ((cur_goal->g_info.attach_info.flags & GAF_ALIGNED) && (obj->mtype.phys_info.flags & PF_LEVELING)) {
                obj->mtype.phys_info.flags &= (~PF_LEVELING);
                cur_goal->g_info.attach_info.flags |= GAF_TEMP_CLEAR_AUTOLEVEL;
              }

              // Determine that attach pos and orient
              if ((cur_goal->g_info.attach_info.flags & GAF_ALIGNED) &&
                  AttachDoPosOrient(obj, p_ap, g_obj, c_ap, true, false, &pos, &orient,
                                    (cur_goal->type == AIG_PLACE_OBJ_ON_OBJ))) {
                bool f_at_pos = AIMoveTowardsPosition(obj, &pos, 1.0f, true, &goal_mdir, &goal_f_moved);
                goal_mset = true;
                if (!goal_f_moved) {
                  AIMoveTowardsDir(obj, &goal_mdir);
                }

                bool f_orient = AITurnTowardsMatrix(obj, obj->ai_info->max_turn_rate, &orient);

                if (f_at_pos && f_orient) {
                  int goal_index = cur_goal - ai_info->goals;

                  if (cur_goal->type == AIG_PLACE_OBJ_ON_OBJ) {
                    UnattachFromParent(child_obj);
                    AttachObject(g_obj, c_ap, child_obj, p_ap, true);
                  } else {
                    if (cur_goal->flags & GF_IS_ATTACH_CHILD)
                      AttachObject(g_obj, c_ap, obj, p_ap, true);
                    else
                      AttachObject(obj, p_ap, g_obj, c_ap, true);
                  }

                  if (cur_goal->g_info.attach_info.flags & GAF_TEMP_CLEAR_ROBOT_COLLISIONS) {
                    obj->mtype.phys_info.flags &= (~PF_NO_ROBOT_COLLISIONS);
                  }
                  if (cur_goal->g_info.attach_info.flags & GAF_TEMP_POINT_COLLIDE_WALLS) {
                    obj->mtype.phys_info.flags &= (~PF_POINT_COLLIDE_WALLS);
                  }
                  if (cur_goal->g_info.attach_info.flags & GAF_TEMP_CLEAR_AUTOLEVEL) {
                    obj->mtype.phys_info.flags |= PF_LEVELING;
                  }
                  cur_goal->g_info.attach_info.flags &=
                      ~(GAF_TEMP_CLEAR_AUTOLEVEL | GAF_TEMP_POINT_COLLIDE_WALLS | GAF_TEMP_CLEAR_ROBOT_COLLISIONS);

                  cur_goal->flags &= ~(GF_NONFLUSHABLE | GF_KEEP_AT_COMPLETION);
                  GoalClearGoal(obj, cur_goal, AIN_GOAL_COMPLETE);
                }
              } else if ((cur_goal->g_info.attach_info.flags & GAF_SPHERE) &&
                         AttachDoPosOrientRad(obj, p_ap, g_obj, rad, &pos)) {
                bool f_at_pos = AIMoveTowardsPosition(obj, &pos, 1.0f, true, &goal_mdir, &goal_f_moved);
                goal_mset = true;
                if (!goal_f_moved) {
                  AIMoveTowardsDir(obj, &goal_mdir);
                }

                if (f_at_pos) {
                  int goal_index = cur_goal - ai_info->goals;

                  AttachObject(obj, p_ap, g_obj, rad);

                  if (cur_goal->g_info.attach_info.flags & GAF_TEMP_CLEAR_ROBOT_COLLISIONS) {
                    obj->mtype.phys_info.flags &= (~PF_NO_ROBOT_COLLISIONS);
                  }
                  if (cur_goal->g_info.attach_info.flags & GAF_TEMP_POINT_COLLIDE_WALLS) {
                    obj->mtype.phys_info.flags &= (~PF_POINT_COLLIDE_WALLS);
                  }
                  if (cur_goal->g_info.attach_info.flags & GAF_TEMP_CLEAR_AUTOLEVEL) {
                    obj->mtype.phys_info.flags |= PF_LEVELING;
                  }
                  cur_goal->g_info.attach_info.flags &=
                      ~(GAF_TEMP_CLEAR_AUTOLEVEL | GAF_TEMP_POINT_COLLIDE_WALLS | GAF_TEMP_CLEAR_ROBOT_COLLISIONS);

                  cur_goal->flags &= ~(GF_NONFLUSHABLE | GF_KEEP_AT_COMPLETION);
                  GoalClearGoal(obj, cur_goal, AIN_GOAL_COMPLETE);
                }
              } else {
                cur_goal->flags &= ~(GF_NONFLUSHABLE | GF_KEEP_AT_COMPLETION);
                GoalClearGoal(obj, cur_goal, AIN_GOAL_INVALID);
              }
              return;
            } else if (ai_info->path.num_paths &&
                       !((cur_goal->status_reg & AISR_SEES_GOAL) && (cur_goal->flags & GF_USE_BLINE_IF_SEES_GOAL))) {
              AIPathMoveTurnTowardsNode(obj, &goal_mdir, &goal_f_moved);
              goal_mset = true;
            } else if (cur_goal->type == AIG_GET_TO_POS || cur_goal->type == AIG_WANDER_AROUND) {
              bool result = AIMoveTowardsPosition(obj, &cur_goal->g_info.pos, 1.0f,
                                                  fabs(cur_goal->circle_distance) < .001, &goal_mdir, &goal_f_moved);
              goal_mset = true;

              if (result && (fabs(cur_goal->circle_distance) < .001))
                GoalClearGoal(obj, cur_goal, AIN_GOAL_COMPLETE);
            } else if (OBJGOAL(cur_goal)) {
              object *g_obj = ObjGet(cur_goal->g_info.handle);

              if (g_obj) {
                AIMoveTowardsPosition(obj, &g_obj->pos, 1.0f, false, &goal_mdir, &goal_f_moved);
                goal_mset = true;
              } else {
                mprintf(0, "AIG Warning: No obj for GetToObj.\n");
              }
            } else if (cur_goal->type == AIG_FOLLOW_PATH) {
              mprintf(0, "AIG Warning: Follow path has no path\n");
            }
          } break;

          case AIG_MOVE_RELATIVE_OBJ_VEC: {
            object *goal_obj = ObjGet(cur_goal->g_info.handle);
            float g_circle_dist = cur_goal->circle_distance;

            if (goal_obj) {
              int subtype = cur_goal->subtype;
              int vec_id = (subtype & 0xFFFFFFFE);
              bool f_toward = (subtype & 0x00000001);
              vector *vec;

              // mprintf(0, "Moving relative a type %d\n", obj->type);

              switch (vec_id) {
              case GST_FVEC:
                vec = &goal_obj->orient.fvec;
                break;
              case GST_RVEC:
                vec = &goal_obj->orient.rvec;
                break;
              case GST_UVEC:
                vec = &goal_obj->orient.uvec;
                break;
              default:
                mprintf(0, "Invalid vec in AIG_MOVE_RELATIVE_OBJ_VEC bashing to fvec\n");
                cur_goal->subtype = GST_FVEC | (int)f_toward;
                vec_id = GST_FVEC;
              }

              if (move_relative_object_vec(obj, vec, goal_obj, g_circle_dist, 1.0f, f_toward, &goal_mdir,
                                           &goal_f_moved)) {
                GoalClearGoal(obj, cur_goal, AIN_GOAL_COMPLETE);
              }
              goal_mset = true;
            } else {
              GoalClearGoal(obj, cur_goal, AIN_GOAL_INVALID);
            }
          } break;

          case AIG_MOVE_RELATIVE_OBJ: // chrishack make this out of other goals
          {
            object *goal_obj = ObjGet(cur_goal->g_info.handle);
            float g_circle_dist = cur_goal->circle_distance;

            int g_status = cur_goal->status_reg;

            //							if((ai_info->ai_type == AIT_MELEE1) &&
            //(ai_info->status_reg & AISR_MELEE))
            //							{
            //								AIMoveTowardsPosition(obj,
            //&ai_info->last_see_target_pos, ai_info->attack_vel_percent);
            //							}
            //							else

            if (ai_info->dist_to_target_perceived < .7f * g_circle_dist) {
              move_away_from_position(obj, &ai_info->last_see_target_pos, ai_info->flee_vel_percent, &goal_mdir,
                                      &goal_f_moved);
              goal_mset = true;

              if (ai_info->sound[AI_FLEE_SOUND] != SOUND_NONE_INDEX) {
                // Plays the sound and makes absolute sure that it is not looping
                if (Gametime - ai_info->last_sound_time[AI_FLEE_SOUND] > 5.0f) {
                  // A 25% chance of playing it
                  if (ps_rand() % 4 == 0) {
                    Sound_system.StopSoundLooping(
                        Sound_system.Play3dSound(ai_info->sound[AI_FLEE_SOUND], SND_PRIORITY_NORMAL, obj));
                    if (Game_mode & GM_MULTI)
                      MultiPlay3dSound(ai_info->sound[AI_FLEE_SOUND], OBJNUM(obj), SND_PRIORITY_NORMAL);
                    if (Demo_flags == DF_RECORDING)
                      DemoWrite3DSound(ai_info->sound[AI_FLEE_SOUND], OBJNUM(obj), SND_PRIORITY_NORMAL);
                  }

                  ai_info->last_sound_time[AI_FLEE_SOUND] = Gametime;
                }
              }
            } else if (g_status & AISR_CIRCLE_DIST) {
              vector movement_vec;
              int gtime = Gametime + OBJNUM(obj);
              gtime = gtime % 8;

              object *rel_obj;

              if (ai_info->flags & AIF_ORIENT_TO_VEL)
                rel_obj = goal_obj;
              else
                rel_obj = obj;

              if (rel_obj) {
                if (gtime < 2)
                  movement_vec = rel_obj->orient.rvec;
                else if (gtime < 4)
                  movement_vec = -rel_obj->orient.rvec;
                else if (gtime < 6) {
                  if (obj->movement_type != MT_WALKING) {
                    movement_vec = rel_obj->orient.uvec;
                  } else {
                    movement_vec = -rel_obj->orient.rvec;
                  }
                } else {
                  if (obj->movement_type != MT_WALKING) {
                    movement_vec = -rel_obj->orient.uvec;
                  } else {
                    movement_vec = rel_obj->orient.rvec;
                  }
                }
              } else {
                movement_vec = obj->orient.rvec;
              }

              if (obj->movement_type == MT_WALKING) {
                int16_t robots[6];
                int num_robots =
                    fvi_QuickDistObjectList(&obj->pos, obj->roomnum, 30.0f, robots, 6, false, true, false, true);
                vector d = Zero_vector;
                int i;
                float closest = 100000.0f;

                if (num_robots > 0) {
                  for (i = 0; i < num_robots; i++) {
                    if (Objects[robots[i]].type == obj->type && Objects[robots[i]].id == obj->id) {
                      vector dir;
                      float distance;

                      // Reverse of move towards
                      dir = obj->pos - Objects[robots[i]].pos;
                      distance = vm_NormalizeVector(&dir);

                      if (distance > 0.0) {
                        if (distance < closest) {
                          closest = distance;
                        }

                        if (distance < 30.0) {
                          d += (1.0f - distance / 30.f) * dir;
                        }
                      }
                    }
                  }
                }

                if (d != Zero_vector) {
                  if (closest < 30.0f) {
                    float scale = 1.0f - closest / 30.0f;
                    vm_NormalizeVector(&d);

                    movement_vec = (scale * d) + (1.0f - scale) * movement_vec;
                    vm_NormalizeVector(&movement_vec);
                  }
                }

                goal_mdir = movement_vec;
                goal_mset = true;
                //									AIMoveTowardsDir(obj,
                //&movement_vec);
              } else {
                goal_mdir = movement_vec;
                goal_mset = true;
                //									AIMoveTowardsDir(obj,
                //&movement_vec);
              }
            } else {
              AIMoveTowardsPosition(obj, &ai_info->last_see_target_pos, 1.0f, false, &goal_mdir, &goal_f_moved);
              goal_mset = true;
            }
          } break;

          default: {
            mprintf(0, "AI ERROR: Object %d trying a non-implemented goal\n", OBJNUM(obj));
            AIMoveTowardsPosition(obj, &ai_info->last_see_target_pos, 1.0f, true, &goal_mdir, &goal_f_moved);
            goal_mset = true;
          }
          }
        } else {
          if (!(f_dodge || f_avoid ||
                (ai_info->dodge_till_time >= Gametime && ai_info->last_dodge_dir != Zero_vector))) {
            AIMoveTowardsPosition(obj, &obj->pos, 1.0f, false, &goal_mdir, &goal_f_moved);
            goal_mset = true;
          }
        }

        // BLEND THIS!
        if ((f_dodge || f_avoid || (ai_info->dodge_till_time >= Gametime && ai_info->last_dodge_dir != Zero_vector)) ||
            (!goal_f_moved && goal_mset)) {
          if (!f_dodge && (ai_info->dodge_till_time >= Gametime && ai_info->last_dodge_dir != Zero_vector)) {
            f_dodge = true;
            ai_info->movement_dir += ai_info->last_dodge_dir;

            if (ai_info->dodge_vel_percent > highest_speed) {
              highest_speed = ai_info->dodge_vel_percent;
            }
          }

          if (!goal_f_moved && goal_mset) {
            ai_info->movement_dir += goal_mdir * cur_goal->influence;
          }

          float move_len = vm_NormalizeVector(&ai_info->movement_dir);
          if (move_len == 0.0f) {
            vm_MakeRandomVector(&ai_info->movement_dir);
            vm_NormalizeVector(&ai_info->movement_dir);
          }

          AIMoveTowardsDir(obj, &ai_info->movement_dir, highest_speed);
          f_turned = false;
        }
      }
    }

    // Handle orientation now
    if ((!f_turned ||
         ((!f_goal_found && Gametime - ai_info->last_see_target_time < 5.0f) &&
          (!f_goal_found && Gametime - ai_info->last_hear_target_time < 5.0f) && (ai_info->flags & AIF_FIRE))) &&
        ai_info->max_turn_rate > 0.0f)
      AIDoOrient(obj, highest_influence_goal);
  }
}

#define MAX_NOT_SEE_TARGET_FIRE_TIME 2.0f
#define MIN_TURRET_SOUND_TIME 0.8f
#define DEFAULT_FIRE_DOT .93f

void ai_fire(object *obj) {
  if (!Object_info[obj->id].static_wb) {
    // something is hosed due to 'Mac memory savings' (c)
    Int3();
    return; // object can't fire anything...
  }

  ai_frame *ai_info = obj->ai_info;
  int i;
  int j;
  poly_model *pm = &Poly_models[obj->rtype.pobj_info.model_num];
  object_info *obj_info = &Object_info[obj->id];
  bool f_turret_next_move_still;

  //.		mprintf(0, "Aiming\n");
  if (!(ai_info->flags & AIF_FIRE)) {
    if (ai_info->status_reg & AISR_RANGED_ATTACK) {
      for (i = 0; i < pm->num_wbs; i++) {
        if (!(obj->dynamic_wb[i].flags & DWBF_ENABLED))
          continue;

        if (WBIsBatteryReady(obj, &obj_info->static_wb[i], i) &&
            !(Cinematic_inuse && !(ai_info->status_reg & AISR_OK_TO_FIRE_DURING_CINEMATICS))) {
          int anim_type = obj_info->static_wb[i].flags & WBF_ANIM_MASKS;

          if (anim_type == WBF_ANIM_LOCAL) {
            WBSetupFireAnim(obj, &obj_info->static_wb[i], i);
          } else if (anim_type == WBF_ANIM_FULL) {
            gi_fire attack_info;

            attack_info.cur_wb = i;
            attack_info.cur_mask = obj->dynamic_wb[i].cur_firing_mask;

            GoalAddGoal(obj, AIG_FIRE_AT_OBJ, (void *)&attack_info, ACTIVATION_BLEND_LEVEL);
          } else {
            WBFireBattery(obj, &obj_info->static_wb[i], i);
            ai_info->status_reg &= ~AISR_RANGED_ATTACK;
          }
        }
      }
    }

    return;
  }

  if (((Gametime - ai_info->last_see_target_time) > 4.0 && (Gametime - ai_info->last_hear_target_time) > 4.0) ||
      ai_info->awareness <= AWARE_BARELY) {
    ai_info->status_reg &= ~AISR_RANGED_ATTACK;
    return;
  }

  for (i = 0; i < pm->num_wbs; i++) {
    vector target_dir[3];
    float dot[3];
    vector gun_point[3];
    vector gun_normal[3];
    float ta[3];
    int best_dot = WB_MOVE_STILL;

    if (!(obj->dynamic_wb[i].flags & DWBF_ENABLED))
      continue;

    if (obj_info->static_wb[i].flags & WBF_USE_CUSTOM_MAX_DIST) {
      float max_dist = obj_info->static_wb[i].aiming_3d_dist;

      if (max_dist < ai_info->dist_to_target_actual)
        continue;
    }

    int aiming_gp_index = obj_info->static_wb[i].aiming_gp_index;

    // The WBF_AIM_FVEC and WBF_FIRE_FVEC stuff will work with a dummy turret or with no turrets
    if (pm->poly_wb[i].num_turrets == 0 ||
        (pm->poly_wb[i].num_turrets == 1 && pm->submodel[pm->poly_wb[i].turret_index[0]].fov == 0.0f)) {
      if (WBIsBatteryReady(obj, &obj_info->static_wb[i], i) &&
          !(Cinematic_inuse && !(ai_info->status_reg & AISR_OK_TO_FIRE_DURING_CINEMATICS))) {
        if (obj_info->static_wb[i].flags & WBF_AIM_FVEC) {
          gun_point[WB_MOVE_STILL] = obj->pos;
          gun_normal[WB_MOVE_STILL] = obj->orient.fvec;

          if (obj_info->static_wb[i].flags & WBF_FIRE_FVEC) {
            gun_normal[WB_MOVE_STILL] = obj->orient.fvec;
          }
        }
        if (obj_info->static_wb[i].flags & WBF_FIRE_FVEC) {
          WeaponCalcGun(&gun_point[WB_MOVE_STILL], NULL, obj, pm->poly_wb[i].gp_index[aiming_gp_index]);
          gun_normal[WB_MOVE_STILL] = obj->orient.fvec;
        } else {
          WeaponCalcGun(&gun_point[WB_MOVE_STILL], &gun_normal[WB_MOVE_STILL], obj,
                        pm->poly_wb[i].gp_index[aiming_gp_index]);
        }

        target_dir[WB_MOVE_STILL] = ai_info->last_see_target_pos - gun_point[WB_MOVE_STILL];
        vm_NormalizeVector(&target_dir[WB_MOVE_STILL]);
        dot[WB_MOVE_STILL] = gun_normal[WB_MOVE_STILL] * target_dir[WB_MOVE_STILL];

        best_dot = WB_MOVE_STILL;
      }
    }

    for (j = 0; j < pm->poly_wb[i].num_turrets; j++) {
      f_turret_next_move_still = false;
      best_dot = WB_MOVE_STILL;
      float min_invalid_ang;
      float max_invalid_ang;
      bool f_constrain = true;

      float s_scale =
          (((obj->ai_info->flags & AIF_TEAM_MASK) != AIF_TEAM_REBEL)) ? Diff_ai_turret_speed[DIFF_LEVEL] : 1.0f;
      const float rps = pm->submodel[pm->poly_wb[i].turret_index[j]].rps * s_scale;

      if (pm->submodel[pm->poly_wb[i].turret_index[j]].fov >
          0.0f) // Gametime >= obj->dynamic_wb[i].turret_next_think_time[j])
      {
        min_invalid_ang = pm->submodel[pm->poly_wb[i].turret_index[j]].fov;
        max_invalid_ang = 1.0 - min_invalid_ang;

        if (min_invalid_ang >= 0.5f)
          f_constrain = false;

        ta[WB_MOVE_STILL] = obj->dynamic_wb[i].norm_turret_angle[j];

        ta[WB_MOVE_RIGHT] = obj->dynamic_wb[i].norm_turret_angle[j] - Frametime * rps;
        while (ta[WB_MOVE_RIGHT] < 0.0)
          ta[WB_MOVE_RIGHT] += 1.0f;

        if (f_constrain && ta[WB_MOVE_RIGHT] > min_invalid_ang && ta[WB_MOVE_RIGHT] < max_invalid_ang)
          ta[WB_MOVE_RIGHT] = max_invalid_ang;

        ta[WB_MOVE_LEFT] = obj->dynamic_wb[i].norm_turret_angle[j] + Frametime * rps;
        while (ta[WB_MOVE_LEFT] > 1.0)
          ta[WB_MOVE_LEFT] -= 1.0f;

        if (f_constrain && ta[WB_MOVE_LEFT] > min_invalid_ang && ta[WB_MOVE_LEFT] < max_invalid_ang)
          ta[WB_MOVE_LEFT] = min_invalid_ang;

        WeaponCalcGun(&gun_point[WB_MOVE_STILL], &gun_normal[WB_MOVE_STILL], obj,
                      pm->poly_wb[i].gp_index[aiming_gp_index]);

        obj->dynamic_wb[i].norm_turret_angle[j] = ta[WB_MOVE_RIGHT];
        WeaponCalcGun(&gun_point[WB_MOVE_RIGHT], &gun_normal[WB_MOVE_RIGHT], obj,
                      pm->poly_wb[i].gp_index[aiming_gp_index]);

        obj->dynamic_wb[i].norm_turret_angle[j] = ta[WB_MOVE_LEFT];
        WeaponCalcGun(&gun_point[WB_MOVE_LEFT], &gun_normal[WB_MOVE_LEFT], obj,
                      pm->poly_wb[i].gp_index[aiming_gp_index]);

        // mprintf(0, "Weapon %f, %f, %f and normal %f, %f, %f\n", XYZ(&gun_point), XYZ(&gun_normal));

        target_dir[WB_MOVE_STILL] = ai_info->last_see_target_pos - gun_point[WB_MOVE_STILL];
        target_dir[WB_MOVE_RIGHT] = ai_info->last_see_target_pos - gun_point[WB_MOVE_RIGHT];
        target_dir[WB_MOVE_LEFT] = ai_info->last_see_target_pos - gun_point[WB_MOVE_LEFT];

        vm_NormalizeVector(&target_dir[WB_MOVE_STILL]);
        vm_NormalizeVector(&target_dir[WB_MOVE_RIGHT]);
        vm_NormalizeVector(&target_dir[WB_MOVE_LEFT]);

        dot[WB_MOVE_STILL] = gun_normal[WB_MOVE_STILL] * target_dir[WB_MOVE_STILL];
        dot[WB_MOVE_RIGHT] = gun_normal[WB_MOVE_RIGHT] * target_dir[WB_MOVE_RIGHT];
        dot[WB_MOVE_LEFT] = gun_normal[WB_MOVE_LEFT] * target_dir[WB_MOVE_LEFT];

        if (dot[WB_MOVE_RIGHT] > dot[WB_MOVE_STILL])
          best_dot = WB_MOVE_RIGHT;
        if (dot[WB_MOVE_LEFT] > dot[best_dot])
          best_dot = WB_MOVE_LEFT;

        obj->dynamic_wb[i].norm_turret_angle[j] = ta[best_dot];

        uint8_t last_t_d = obj->dynamic_wb[i].turret_direction[j];

        if (dot[WB_MOVE_RIGHT] > dot[WB_MOVE_LEFT])
          obj->dynamic_wb[i].turret_direction[j] = WB_MOVE_RIGHT;
        else
          obj->dynamic_wb[i].turret_direction[j] = WB_MOVE_LEFT;

        if (last_t_d != obj->dynamic_wb[i].turret_direction[j]) {
          if (ai_info->sound[AI_TURRET_SOUND] != SOUND_NONE_INDEX &&
              (ai_info->last_sound_time[AI_TURRET_SOUND] + MIN_TURRET_SOUND_TIME <= Gametime)) {
            // Plays the sound and makes absolute sure that it is not looping
            Sound_system.StopSoundLooping(
                Sound_system.Play3dSound(ai_info->sound[AI_TURRET_SOUND], SND_PRIORITY_NORMAL, obj));
            if (Game_mode & GM_MULTI)
              MultiPlay3dSound(ai_info->sound[AI_TURRET_SOUND], OBJNUM(obj), SND_PRIORITY_NORMAL);
            if (Demo_flags == DF_RECORDING)
              DemoWrite3DSound(ai_info->sound[AI_TURRET_SOUND], OBJNUM(obj), SND_PRIORITY_NORMAL);

            ai_info->last_sound_time[AI_TURRET_SOUND] = Gametime;
          }
        }

        obj->dynamic_wb[i].turret_next_think_time[j] += pm->submodel[pm->poly_wb[i].turret_index[j]].think_interval;
        if (Demo_flags == DF_RECORDING) {
          DemoWriteTurretChanged(OBJNUM(obj));
        }
        if (Game_mode & GM_MULTI) {
          MultiAddObjTurretUpdate(OBJNUM(obj));
        }

      } else {
        best_dot = obj->dynamic_wb[i].turret_direction[j];

        if (best_dot != WB_MOVE_STILL) {
          min_invalid_ang = pm->submodel[pm->poly_wb[i].turret_index[j]].fov;
          max_invalid_ang = 1.0 - min_invalid_ang;

          if (min_invalid_ang >= 0.5f)
            f_constrain = false;
        }

        // chrishack -- make next still
        switch (best_dot) {
        case WB_MOVE_STILL:
          ta[WB_MOVE_STILL] = obj->dynamic_wb[i].norm_turret_angle[j];
          break;

        case WB_MOVE_RIGHT:
          ta[WB_MOVE_RIGHT] = obj->dynamic_wb[i].norm_turret_angle[j] - Frametime * rps;
          while (ta[WB_MOVE_RIGHT] < 0.0)
            ta[WB_MOVE_RIGHT] += 1.0f;

          if (f_constrain && ta[WB_MOVE_RIGHT] > min_invalid_ang && ta[WB_MOVE_RIGHT] < max_invalid_ang) {
            ta[WB_MOVE_RIGHT] = max_invalid_ang;
            f_turret_next_move_still = true;
          }
          break;

        case WB_MOVE_LEFT:
          ta[WB_MOVE_LEFT] = obj->dynamic_wb[i].norm_turret_angle[j] + Frametime * rps;
          while (ta[WB_MOVE_LEFT] > 1.0)
            ta[WB_MOVE_LEFT] -= 1.0f;

          if (f_constrain && ta[WB_MOVE_LEFT] > min_invalid_ang && ta[WB_MOVE_LEFT] < max_invalid_ang) {
            ta[WB_MOVE_LEFT] = min_invalid_ang;
            f_turret_next_move_still = true;
          }
          break;
        }

        obj->dynamic_wb[i].norm_turret_angle[j] = ta[best_dot];

        if (WBIsBatteryReady(obj, &obj_info->static_wb[i], i) &&
            !(Cinematic_inuse && !(ai_info->status_reg & AISR_OK_TO_FIRE_DURING_CINEMATICS))) {
          WeaponCalcGun(&gun_point[best_dot], &gun_normal[best_dot], obj, pm->poly_wb[i].gp_index[aiming_gp_index]);

          target_dir[best_dot] = ai_info->last_see_target_pos - gun_point[best_dot];
          vm_NormalizeVector(&target_dir[best_dot]);
          dot[best_dot] = gun_normal[best_dot] * target_dir[best_dot];
        }
      }

      // This happens on a non-thinking frame the the turret hits a constrain
      if (f_turret_next_move_still)
        obj->dynamic_wb[i].turret_direction[j] = WB_MOVE_STILL;
    }

    if (Gametime - ai_info->last_see_target_time < MAX_NOT_SEE_TARGET_FIRE_TIME ||
        Gametime - ai_info->last_hear_target_time < MAX_NOT_SEE_TARGET_FIRE_TIME) {
      if (WBIsBatteryReady(obj, &obj_info->static_wb[i], i) &&
          !(Cinematic_inuse && !(ai_info->status_reg & AISR_OK_TO_FIRE_DURING_CINEMATICS))) {
        float fire_dot;

        if (obj_info->static_wb[i].flags & WBF_USE_CUSTOM_FOV)
          fire_dot = obj_info->static_wb[i].aiming_3d_dot;
        else
          fire_dot = DEFAULT_FIRE_DOT;

        if (dot[best_dot] >= fire_dot) {
          bool f_no_fire = false;
          int anim_type = obj_info->static_wb[i].flags & WBF_ANIM_MASKS;

          if (ai_info->agression == 0.0f && ai_info->memory[0].num_times_hit == 0) {
            // Assume no fire
            f_no_fire = true;

            object *target = ObjGet(ai_info->target_handle);
            if (target) {
              fvi_query fq;
              fvi_info hit_info;
              int fate;
              int ignore_obj_list[100];
              ignore_obj_list[0] = OBJNUM(obj);
              int num_ignored = 1;
              int i;

              // CHRISHACK - ONLY IGNORES FIRST LEVEL OF CHILDREN - DO RECERSIVE
              for (i = 0; i < Poly_models[obj->rtype.pobj_info.model_num].n_attach; i++) {
                object *child;

                if ((child = ObjGet(obj->attach_children[i])) != NULL && num_ignored < 99) {
                  ignore_obj_list[num_ignored++] = OBJNUM(child);
                }
              }

              ignore_obj_list[num_ignored] = -1;

              fq.p0 = &obj->pos;
              fq.p1 = &target->pos;
              fq.startroom = obj->roomnum;

              fq.rad = 0.01f;
              fq.flags = FQ_CHECK_OBJS | FQ_IGNORE_WEAPONS | FQ_IGNORE_POWERUPS | FQ_IGNORE_RENDER_THROUGH_PORTALS |
                         FQ_NO_RELINK;
              fq.thisobjnum = -1;
              fq.ignore_obj_list = ignore_obj_list;

              fate = fvi_FindIntersection(&fq, &hit_info);

              if (fate != HIT_TERRAIN && fate != HIT_WALL &&
                  (((fate == HIT_OBJECT || fate == HIT_SPHERE_2_POLY_OBJECT) &&
                    hit_info.hit_object[0] == OBJNUM(target)) ||
                   fate == HIT_NONE)) {
                f_no_fire = false;
              }
            }
          }

          if (!f_no_fire) {
            if (anim_type == WBF_ANIM_LOCAL) {
              WBSetupFireAnim(obj, &obj_info->static_wb[i], i);
            } else if (anim_type == WBF_ANIM_FULL) {
              gi_fire attack_info;

              attack_info.cur_wb = i;
              attack_info.cur_mask = obj->dynamic_wb[i].cur_firing_mask;

              GoalAddGoal(obj, AIG_FIRE_AT_OBJ, (void *)&attack_info, ACTIVATION_BLEND_LEVEL);
            } else {
              WBFireBattery(obj, &obj_info->static_wb[i], i);
              ai_info->status_reg &= ~AISR_RANGED_ATTACK;
            }
          } else {
            ai_info->status_reg &= ~AISR_RANGED_ATTACK;
            obj->dynamic_wb[i].last_fire_time = Gametime + 1.0f + ps_rand() / (float)D3_RAND_MAX;
          }
        }
      }
    }
  }
}

#define PERCENT_QUIRK_PER_SEC .1
#define PERCENT_TAUNT_PER_SEC .1

static inline void do_awareness_based_anim_stuff(object *obj) {
  int next_anim;
  ai_frame *ai_info = obj->ai_info;

  if (ai_info->awareness <= AWARE_BARELY) {
    if (ai_info->animation_type == AS_ALERT && ai_info->next_animation_type != AS_GOTO_ALERT_STANDING) {
      next_anim = AS_IDLE;
      GoalAddGoal(obj, AIG_SET_ANIM, (void *)&next_anim, ACTIVATION_BLEND_LEVEL);
    } else if (ai_info->animation_type == AS_IDLE && ai_info->next_animation_type != AS_GOTO_IDLE_STANDING) {
      float local_seed = OBJNUM(obj) / 32.0f;

      int new_time_int = Gametime + local_seed;
      int last_time_int = Gametime - Frametime + local_seed;

      // Once a second we have a chance of doing a quirk
      if (new_time_int != last_time_int) {
        if (ps_rand() < D3_RAND_MAX * PERCENT_QUIRK_PER_SEC) {
          next_anim = AS_QUIRK;
          GoalAddGoal(obj, AIG_SET_ANIM, (void *)&next_anim, ACTIVATION_BLEND_LEVEL);
        }
      }
    }
  } else if (ai_info->animation_type == AS_IDLE || ai_info->animation_type == AS_QUIRK ||
             ai_info->animation_type == AS_BIRTH) {
    next_anim = AS_ALERT;
    GoalAddGoal(obj, AIG_SET_ANIM, (void *)&next_anim, ACTIVATION_BLEND_LEVEL);
  } else if (ai_info->animation_type == AS_ALERT) {
    if (!(ai_info->flags & AIF_ONLY_TAUNT_AT_DEATH) &&
        (Object_info[obj->id].anim[ai_info->movement_type].elem[AS_TAUNT].to != 0.0f)) {
      float local_seed = OBJNUM(obj) / 32.0f;

      int new_time_int = Gametime + local_seed;
      int last_time_int = Gametime - Frametime + local_seed;

      // Once a second we have a chance of doing a quirk
      if (new_time_int != last_time_int) {
        if (ps_rand() < D3_RAND_MAX * PERCENT_TAUNT_PER_SEC) {
          next_anim = AS_TAUNT;
          GoalAddGoal(obj, AIG_SET_ANIM, (void *)&next_anim, ACTIVATION_BLEND_LEVEL);
        }
      }
    }
  }
}

static inline void ai_decrease_awareness(object *obj) {
  ai_frame *ai_info = obj->ai_info;

  if (ai_info->awareness == AWARE_NONE && !(ai_info->flags & AIF_PERSISTANT)) {
#ifdef _DEBUG
    if (AI_debug_robot_do && OBJNUM(obj) == AI_debug_robot_index) {
      mprintf(0, "AI Note: In free path\n");
    }
#endif
    AIPathFreePath(&ai_info->path);
  }

  if (Gametime - ai_info->last_render_time < AWARENESS_RENDER_RECENTLY_INTERVAL ||
      Gametime - ai_info->last_see_target_time < AWARENESS_SEE_TARGET_RECENTLY_INTERVAL ||
      Gametime - ai_info->last_hear_target_time < AWARENESS_SEE_TARGET_RECENTLY_INTERVAL)
    ai_info->awareness -= (AWARE_RENDER_RECENTLY_FALLOFF * Frametime);
  else
    ai_info->awareness -= (AWARE_FALLOFF * Frametime);

  if (ai_info->awareness < AWARE_NONE) {
    ai_info->awareness = AWARE_NONE;
  }

  //	mprintf(0, "Awareness %f", ai_info->awareness);
}

static inline bool ai_do_script_stuff(object *obj) {
  tOSIRISEventInfo ei;
  Osiris_CallEvent(obj, EVT_AI_FRAME, &ei);
  //@$-D3XExecScript(obj, EVT_AI_FRAME, NULL, REF_OBJTYPE, NULL);

  return true;
}

static inline void ai_walker_stuff(object *obj) {
  ai_frame *ai_info = obj->ai_info;

  // Do standing->walking and walking->standing stuff
  if (ai_info->movement_type == MC_STANDING) {
    int next_anim;

    if (vm_GetMagnitude(&obj->mtype.phys_info.velocity) > 0.01f ||
        vm_GetMagnitude(&obj->mtype.phys_info.rotvel) > 0.01) {
      if (ai_info->next_animation_type == AI_INVALID_INDEX) {
        if (ai_info->animation_type == AS_ALERT) {
          next_anim = AS_GOTO_ALERT_WALKING;
          GoalAddGoal(obj, AIG_SET_ANIM, (void *)&next_anim, ACTIVATION_BLEND_LEVEL);
        } else if (ai_info->animation_type == AS_IDLE || ai_info->animation_type == AS_QUIRK ||
                   ai_info->animation_type == AS_BIRTH) {
          next_anim = AS_GOTO_IDLE_WALKING;
          GoalAddGoal(obj, AIG_SET_ANIM, (void *)&next_anim, ACTIVATION_BLEND_LEVEL);
        }
      }

      obj->mtype.phys_info.velocity = Zero_vector;
    }
  } else if (ai_info->movement_type == MC_WALKING) {
    int next_anim;

    if (vm_GetMagnitude(&obj->mtype.phys_info.velocity) <= 0.01f &&
        vm_GetMagnitude(&obj->mtype.phys_info.rotvel) <= 0.01) {
      if (ai_info->animation_type == AS_ALERT) {
        next_anim = AS_GOTO_ALERT_STANDING;
        GoalAddGoal(obj, AIG_SET_ANIM, (void *)&next_anim, ACTIVATION_BLEND_LEVEL);
      } else if (ai_info->animation_type == AS_IDLE) {
        next_anim = AS_GOTO_IDLE_STANDING;
        GoalAddGoal(obj, AIG_SET_ANIM, (void *)&next_anim, ACTIVATION_BLEND_LEVEL);
      }
    }
  }
}

int AIGetTeam(object *obj) {
  int t_team;

  if (obj->type == OBJ_PLAYER) {
    if (Num_teams > 1 || ((Game_mode & GM_MULTI) && Num_teams <= 1 && !(Netgame.flags & NF_DAMAGE_FRIENDLY))) {
      t_team = AIF_TEAM_REBEL + PlayerGetTeam(obj->id) + 1;
      //@@t_team = AIF_TEAM_REBEL + Players[obj->id].team + 1;
    } else {
      t_team = AIF_TEAM_REBEL + obj->id + 1;
    }
  } else {
    if (obj->ai_info->flags & AIF_ACT_AS_NEUTRAL_UNTIL_SHOT) {
      t_team = AIF_TEAM_NEUTRAL;
    } else {
      t_team = obj->ai_info->flags & AIF_TEAM_MASK;

      if (t_team == AIF_TEAM_REBEL) {
        object *p = ObjGet(obj->parent_handle);

        if (p && (p->type == OBJ_PLAYER || p->type == OBJ_GHOST)) {
          if (Num_teams > 1) {
            t_team += PlayerGetTeam(p->id) + 1;
            //@@t_team += Players[p->id].team + 1;
          } else {
            t_team += p->id + 1;
          }
        }
      }
    }
  }

  return t_team;
}

bool AIObjFriend(object *obj, object *target) {
  bool f_friend = false;

  // If an object isn't an AI object, it isn't a friend
  if (!obj || !target || (target->type != OBJ_PLAYER && !target->ai_info) || (obj->type != OBJ_PLAYER && !obj->ai_info))
    return false;

  if (obj->type == OBJ_GHOST || obj->type == OBJ_POWERUP || (obj->flags & OF_DESTROYED))
    return false;

  if ((target->control_type == CT_AI) && (target->movement_type == MT_NONE) &&
      Poly_models[target->rtype.pobj_info.model_num].num_wbs == 0) {
    return false;
  }

  if (obj->type == OBJ_PLAYER && (Players[obj->id].flags & PLAYER_FLAGS_DEAD))
    return false;

  int team = AIGetTeam(obj);
  int t_team = AIGetTeam(target);

  // If this object is targetting you - it is your enemy
  if ((target->control_type == CT_AI) && (target->ai_info->target_handle == obj->handle)) {
    return false;
  }

  // If its neutral and not targetting you -- its not an enemy (unless your hostile)
  if (team == AIF_TEAM_HOSTILE)
    return false;

  // Related objects shouldn't kill each other
  if (ObjectsAreRelated(OBJNUM(obj), OBJNUM(target))) {
    return true;
  }

  if (obj->parent_handle == target->handle || target->parent_handle == obj->handle) {
    return true;
  }

  switch (team) {
  case AIF_TEAM_PTMC:
    if (t_team == AIF_TEAM_PTMC) {
      f_friend = true;
    }
    break;

  case AIF_TEAM_HOSTILE:
    f_friend = false;
    break;

  case AIF_TEAM_NEUTRAL:

    if (t_team == AIF_TEAM_NEUTRAL) {
      f_friend = true;
    }
    break;

  // A player team
  default:
    // All REBEL sub teams are friends with non player-parented rebels
    if (t_team == AIF_TEAM_REBEL || team == AIF_TEAM_REBEL || t_team == team) {
      f_friend = true;
    }
    break;
  }

  return f_friend;
}

bool AIObjEnemy(object *obj, object *target) {
  bool f_enemy = false;

  // If an object isn't an AI object or player, it isn't an enemy
  if (!obj || !target || (target->type != OBJ_PLAYER && !target->ai_info) || (obj->type != OBJ_PLAYER && !obj->ai_info))
    return false;

  if (obj->type == OBJ_GHOST || obj->type == OBJ_POWERUP || (obj->flags & OF_DESTROYED))
    return false;

  if (obj->type == OBJ_PLAYER && (Players[obj->id].flags & PLAYER_FLAGS_DEAD))
    return false;

  int team = AIGetTeam(obj);
  int t_team = AIGetTeam(target);

  // If this object is targetting you - it is your enemy
  if ((target->control_type == CT_AI) && (target->ai_info->target_handle == obj->handle)) {
    return true;
  }

  if ((target->control_type == CT_AI) && (target->movement_type == MT_NONE) &&
      Poly_models[target->rtype.pobj_info.model_num].num_wbs == 0) {
    return false;
  }

  // If its neutral and not targetting you -- its not an enemy (unless your hostile)
  if ((team != AIF_TEAM_HOSTILE) && (t_team == AIF_TEAM_NEUTRAL && target->ai_info->target_handle != obj->handle)) {
    return false;
  }

  // Related objects shouldn't kill each other
  if (ObjectsAreRelated(OBJNUM(obj), OBJNUM(target))) {
    return false;
  }

  if (obj->parent_handle == target->handle || target->parent_handle == obj->handle) {
    return false;
  }

  switch (team) {
  case AIF_TEAM_PTMC:
    if (t_team != AIF_TEAM_PTMC) {
      f_enemy = true;
    }
    break;

  case AIF_TEAM_HOSTILE:
    f_enemy = true;
    break;

  case AIF_TEAM_NEUTRAL:

    ASSERT(obj->ai_info);

    if (obj->ai_info->target_handle == target->handle) {
      f_enemy = true;
    }
    break;

  // A player team
  default:
    // All REBEL sub teams are friends with non player-parented rebels
    if (t_team == AIF_TEAM_PTMC || t_team == AIF_TEAM_HOSTILE ||
        (t_team != AIF_TEAM_REBEL && team != AIF_TEAM_REBEL && t_team != team &&
         !(((Game_mode & GM_MULTI) && Num_teams <= 1 && !(Netgame.flags & NF_DAMAGE_FRIENDLY))))) {
      f_enemy = true;
    }
    break;
  }

  return f_enemy;
}

#define AI_FORGIVE_AGRESSION_MULTIPLIER 1.2f

void AITargetCheck(object *obj, object *target, object **best_obj, float *best_dot, float *best_dist) {
  bool f_use_dot = (obj->ai_info->flags & AIF_TARGET_BY_DIST) != 0;

  if (AIObjEnemy(obj, target)) {
    float dot;
    float dist;
    vector to_obj;
    fvi_query fq;
    fvi_info hit_info;
    int fate;

    if (obj == target)
      return;

    if (!BOA_IsVisible(obj->roomnum, target->roomnum))
      return;

    if (!AIDetermineObjVisLevel(obj, target))
      return;

    if (target->type == OBJ_PLAYER && (Players[target->id].flags & (PLAYER_FLAGS_DEAD | PLAYER_FLAGS_DYING)))
      return;

    to_obj = target->pos - obj->pos;

    dist = vm_NormalizeVector(&to_obj);

    if (dist > MAX_SEE_TARGET_DIST)
      return;

    vector look_dir;
    AIDetermineFovVec(obj, &look_dir);

    dot = to_obj * look_dir;

    if (f_use_dot && dot <= *best_dot) {
      return;
    } else if (!f_use_dot && dist >= *best_dist) {
      return;
    }

    fq.p0 = &obj->pos;
    fq.p1 = &target->pos;
    fq.startroom = obj->roomnum;

    fq.rad = 0.0f;
    fq.flags = FQ_CHECK_OBJS | FQ_ONLY_DOOR_OBJ | FQ_NO_RELINK;
    fq.thisobjnum = -1;

    int ignore_obj_list[100];
    ignore_obj_list[0] = OBJNUM(obj);
    int num_ignored = 1;
    int i;

    // CHRISHACK - ONLY IGNORES FIRST LEVEL OF CHILDREN - DO RECERSIVE
    for (i = 0; i < Poly_models[obj->rtype.pobj_info.model_num].n_attach; i++) {
      object *child;

      if ((child = ObjGet(obj->attach_children[i])) != NULL && num_ignored < 99) {
        ignore_obj_list[num_ignored++] = OBJNUM(child);
      }
    }

    ignore_obj_list[num_ignored] = -1;
    fq.ignore_obj_list = ignore_obj_list;

    fate = fvi_FindIntersection(&fq, &hit_info);

    if (fate != HIT_NONE)
      return;

    *best_dot = dot;
    *best_dist = dist;
    *best_obj = target;
  }
}

void AIDetermineTarget(object *obj) {
  ai_frame *ai_info = obj->ai_info;
  object *best_obj = NULL;
  float best_dot = -1.0f;
  float best_dist = MAX_SEE_TARGET_DIST + 1;
  int i;

  if (Gametime < ai_info->next_target_update_time)
    return;

  if (ai_info->awareness >= AWARE_BARELY)
    ai_info->next_target_update_time =
        Gametime + MIN_TARGET_UPDATE_INTERVAL +
        ((float)ps_rand() / (float)D3_RAND_MAX) * (MAX_TARGET_UPDATE_INTERVAL - MIN_TARGET_UPDATE_INTERVAL);
  else
    ai_info->next_target_update_time =
        Gametime + 2.0f * MIN_TARGET_UPDATE_INTERVAL +
        ((float)ps_rand() / (float)D3_RAND_MAX) * 2.0f * (MAX_TARGET_UPDATE_INTERVAL - MIN_TARGET_UPDATE_INTERVAL);

  // Chrishack -- if agression is over a value, NO switching targets!!!!!!!!!  Need to implement
  // Chrishack -- if frustration is over a value, act as hostile -- temp stuff AIF_TEAM_HOSTILE

  // They forget their enemies after a few seconds
  if ((ai_info->flags & AIF_TEAM_MASK) == AIF_TEAM_NEUTRAL || (ai_info->flags & AIF_ACT_AS_NEUTRAL_UNTIL_SHOT)) {
    best_obj = NULL;
  } else if ((ai_info->flags & AIF_TEAM_MASK) != AIF_TEAM_PTMC) {
    int16_t list[50];
    int num = fvi_QuickDistObjectList(&obj->pos, obj->roomnum, MAX_SEE_TARGET_DIST, list, 50, false, true, false, true);

    for (i = 0; i < num; i++) {
      AITargetCheck(obj, &Objects[list[i]], &best_obj, &best_dot, &best_dist);
    }
  } else // Team PTMC  :)
  {
    if (Game_mode & GM_MULTI) {
      // Multiplayer targetting (Major difference is that robot will ignore players while infighting in single player)
      for (i = 0; i < MAX_PLAYERS; i++) {
        if ((NetPlayers[i].flags & NPF_CONNECTED) && (NetPlayers[i].sequence >= NETSEQ_PLAYING)) {
          object *target = &Objects[Players[i].objnum];

          AITargetCheck(obj, target, &best_obj, &best_dot, &best_dist);
        }
      }
    } else {
      object *t = ObjGet(ai_info->target_handle);
      bool f_forgive_friend = false;

      if ((t) && (t->control_type == CT_AI) && ((t->ai_info->flags & AIF_TEAM_MASK) == AIF_TEAM_PTMC)) {
        // Do the divide because we don't want D3_RAND_MAX to go too high
        if (ps_rand() / AI_FORGIVE_AGRESSION_MULTIPLIER > ai_info->agression * D3_RAND_MAX) {
          f_forgive_friend = true;
        }
      }

      // chrishack -- FUCK  a multi-guidebot bug!!!!!!
      if (f_forgive_friend || !ai_target_valid(obj) ||
          (ai_info->target_handle != OBJECT_HANDLE_NONE && ai_info->target_handle == Buddy_handle[0] &&
           ObjGet(Buddy_handle[0])->type != OBJ_GHOST)) {
        if (Player_object->type != OBJ_GHOST)
          best_obj = Player_object;
        else if (Buddy_handle[0] != OBJECT_HANDLE_NONE && ObjGet(Buddy_handle[0])->type != OBJ_GHOST)
          best_obj = ObjGet(Buddy_handle[0]);
        else
          best_obj = NULL;
      } else {
        best_obj = ObjGet(obj->ai_info->target_handle);
      }
    }
  }

  if (best_obj) {
    AISetTarget(obj, best_obj->handle);
  } else {
    AISetTarget(obj, OBJECT_HANDLE_NONE);
  }
}

// chrishack -- make sure that some checks are done with a ps_rand() based on the emotion involved
// also current emotional levels should influence the percent chance of the check being successful
void AIDoFreud(object *obj) {
  ai_frame *ai_info = obj->ai_info;
  auto& mem = ai_info->memory;

  int fear_depth = (ai_info->life_preservation) * (AI_MEM_DEPTH - 1) + 1;
  int anger_depth = (ai_info->agression) * (AI_MEM_DEPTH - 1) + 1;
  int frust_depth = (ai_info->frustration) * (AI_MEM_DEPTH - 1) + 1;

  if (fear_depth >= AI_MEM_DEPTH)
    fear_depth = AI_MEM_DEPTH - 1;
  if (anger_depth >= AI_MEM_DEPTH)
    anger_depth = AI_MEM_DEPTH - 1;
  if (frust_depth >= AI_MEM_DEPTH)
    frust_depth = AI_MEM_DEPTH - 1;

  if (ai_info->goals[3].used == 0 && ai_info->awareness > AWARE_BARELY) {
    if (IS_GENERIC(obj->type) && mem[0].shields / Object_info[obj->id].hit_points < ai_info->life_preservation &&
        mem[0].num_enemy_shots_dodged > 0 && mem[0].num_friends < 2 &&
        (float)ps_rand() / (float)D3_RAND_MAX < ai_info->life_preservation) {
      float time = 10.0f * ai_info->life_preservation + 5.0f;

      GoalAddGoal(obj, AIG_WANDER_AROUND, NULL, 3, 2.0f, GF_SPEED_FLEE | GF_ORIENT_VELOCITY | GF_NONFLUSHABLE);
      GoalAddEnabler(obj, 3, AIE_CLEAR_TIME, (void *)&time, 1.0, 0.0);

      mprintf(0, "Fear!!!!\n");
      return;
    }

    // Accounts for massive loss of shields
    if (IS_GENERIC(obj->type) &&
        (mem[fear_depth].shields - mem[0].shields) / mem[fear_depth].shields >
            0.25f * (1.0f - ai_info->life_preservation) &&
        (float)ps_rand() / (float)D3_RAND_MAX < ai_info->life_preservation) {
      float time = 10.0f * ai_info->life_preservation + 5.0f;

      GoalAddGoal(obj, AIG_WANDER_AROUND, NULL, 3, 2.0f, GF_SPEED_FLEE | GF_ORIENT_VELOCITY | GF_NONFLUSHABLE);
      GoalAddEnabler(obj, 3, AIE_CLEAR_TIME, (void *)&time, 1.0, 0.0);

      mprintf(0, "Fear!!!!\n");
      return;
    }

    // If others have died and/or left...  (Me too)
    if (ai_info->life_preservation > 0.5f && mem[fear_depth].num_friends > 0 && mem[0].num_friends == 0 &&
        mem[0].num_enemies > 0) {
      float time = 10.0f * ai_info->life_preservation + 5.0f;

      GoalAddGoal(obj, AIG_WANDER_AROUND, NULL, 3, 2.0f, GF_SPEED_FLEE | GF_ORIENT_VELOCITY | GF_NONFLUSHABLE);
      GoalAddEnabler(obj, 3, AIE_CLEAR_TIME, (void *)&time, 1.0, 0.0);

      mprintf(0, "Fear!!!!\n");
      return;
    }
  }
}

void AIDoMemFrame(object *obj) {
  ai_frame *ai_info = obj->ai_info;
  ai_info->mem_time_till_next_update -= Frametime;

  if (ai_info->mem_time_till_next_update <= 0.0f) {
    int i;

    // Compute next analyze time
    ai_info->mem_time_till_next_update = 3.0f + (float)ps_rand() / (float)D3_RAND_MAX * 2.0f;

    // Do the amount of friends/enemies left and the current shields before running Freud
    int16_t near_objs[100];
    float dist = 100.0f;

    // chrishack -- there must be a better way...
    if (ai_info->coop_team * 300.0f > dist) {
      dist = ai_info->coop_team * 300.0f > dist;
    }

    int num_near = fvi_QuickDistObjectList(&obj->pos, obj->roomnum, dist, near_objs, 100, false, true, false, true);

    ai_info->memory[0].num_enemies = 0;
    ai_info->memory[0].num_friends = 0;

    for (i = 0; i < num_near; i++) {
      object *check_obj = &Objects[near_objs[i]];

      if (check_obj == obj)
        continue;

      if (AIObjEnemy(obj, check_obj))
        ai_info->memory[0].num_enemies++;
      else if (AIObjFriend(obj, check_obj))
        ai_info->memory[0].num_friends++;
    }

    ai_info->memory[0].shields = obj->shields;

    // Do emotions based on new data
    AIDoFreud(obj);

    // Move emotions through the stack
    for (i = AI_MEM_DEPTH - 1; i > 0; i--) {
      ai_info->memory[i] = ai_info->memory[i - 1];
    }

    // Reset the accumulators

    // These are imcremented as this memory time slice is active
    ai_info->memory[0].num_enemy_shots_dodged = 0;
    ai_info->memory[0].num_enemy_shots_fired = 0;
    ai_info->memory[0].num_hit_enemy = 0;
    ai_info->memory[0].num_times_hit = 0;

    // Dummy values, as these are computed at the end of the time frame (as seen above)
    ai_info->memory[0].shields = obj->shields;
    ai_info->memory[0].num_enemies = ai_info->memory[1].num_enemies;
    ai_info->memory[0].num_friends = ai_info->memory[1].num_friends;
  }
}

void AIDoFrame(object *obj) {

  bool f_attach_done = false;
  int multi_saved_weapon_flags;
  char multi_saved_wb_firing;

  // AI objects don't use thrust (in general)
  obj->mtype.phys_info.flags &= ~PF_USES_THRUST;
  obj->mtype.phys_info.rotthrust = Zero_vector;
  obj->mtype.phys_info.thrust = Zero_vector;

  if (obj->type == OBJ_DUMMY)
    return;

  if ((Game_mode & GM_MULTI) && (Netgame.local_role == LR_SERVER)) {
    multi_saved_wb_firing = obj->ai_info->last_special_wb_firing;
    multi_saved_weapon_flags = obj->weapon_fire_flags;
  }

  ai_frame *ai_info = obj->ai_info;
  ASSERT((obj->control_type == CT_AI) || (obj->control_type == CT_DYING_AND_AI));

  if ((ai_info->flags & AIF_DISABLED) || (obj->type == OBJ_DUMMY)) {
    return;
  }

  // Animate the object
  ai_do_animation(obj, Frametime);
  if (ai_info->animation_type == AS_IDLE) {
    f_attach_done = true;
  }

  if (Demo_flags == DF_PLAYBACK) {
    // All we want is animation
    return;
  }
  // Handle On/off and spray weapons
  {
    if ((obj->weapon_fire_flags & WFF_SPRAY) && !(obj->flags & (OF_DESTROYED | OF_DYING))) {
      char wb_index = ai_info->last_special_wb_firing;
      DoSprayEffect(obj, &Object_info[obj->id].static_wb[wb_index], wb_index);
      if (!((Game_mode & GM_MULTI) && (Netgame.local_role == LR_CLIENT))) {
        if (WBIsBatteryReady(obj, &Object_info[obj->id].static_wb[wb_index], wb_index) &&
            !(Cinematic_inuse && !(ai_info->status_reg & AISR_OK_TO_FIRE_DURING_CINEMATICS))) {
          WBFireBattery(obj, &Object_info[obj->id].static_wb[wb_index], wb_index);
        }
      }
    }

    if (obj->weapon_fire_flags & WFF_ON_OFF) {
      FireOnOffWeapon(obj);
    }
  }

  if ((Game_mode & GM_MULTI) && (Netgame.local_role == LR_CLIENT)) {
    if (!f_attach_done) {
      AttachUpdateSubObjects(obj);
      f_attach_done = true;
    }
    return;
  }

  // If awareness if forced, do so
  if ((ai_info->flags & AIF_FORCE_AWARENESS) && (ai_info->awareness < AWARE_MOSTLY)) {
    ai_info->awareness = AWARE_MOSTLY;
  }

  // If not multiplayer - these must be set each frame
  obj->weapon_fire_flags = 0;

  // If the object is dead, it does not think
  if (obj->flags & OF_DEAD) {
    if (!f_attach_done) {
      AttachUpdateSubObjects(obj);
      f_attach_done = true;
    }
    return;
  }

  AIDoMemFrame(obj);

  if (ai_info->flags & AIF_DETERMINE_TARGET)
    AIDetermineTarget(obj);

  // Update the robot's eyes -- gets player distance -- (only if AI cares about player)
  if (ai_info->notify_flags & (0x00000001 << AIN_SEE_TARGET))
    AICheckTargetVis(obj);

  // Updates some of the AI status registers
  ai_update_registers(obj);

  // Have goals result in movement
  // I will think if either the player or me sees anything within 4 seconds
  if ((ai_info->awareness) || (ai_info->flags & AIF_PERSISTANT)) {
    // Does the scripting stuff for an AI
    ai_do_script_stuff(obj);

    if (ai_info->ai_type == AIT_BIRD_FLOCK1)
      ai_info->flags |= AIF_TRACK_CLOSEST_2_FRIENDS; // chrishack -- remove -- testing only

    // Determines all tracked objects
    AIDoTrackFrame(obj);

    // Does goal updating for the frame
    GoalDoFrame(obj);

    // Allow the robot to move
    if (obj->control_type == CT_AI) {
      if (ai_info->animation_type != AS_FLINCH) {
        float speed;

#ifdef _DEBUG
        if (!Game_do_ai_movement) {
          goto after_move;
        }
#endif

        ai_move(obj);

        speed = vm_GetMagnitude(&obj->mtype.phys_info.velocity);

        // Removes the framerate independance from objects moving within 2x of there normal max speed
        if (speed > 0.1f && speed <= ai_info->max_velocity * 2.0) {
          if (obj->mtype.phys_info.drag > 0.0f && obj->mtype.phys_info.mass > 0.0f) {
            obj->mtype.phys_info.flags |= PF_USES_THRUST;
            obj->mtype.phys_info.rotthrust = Zero_vector;
            obj->mtype.phys_info.thrust = obj->mtype.phys_info.velocity * obj->mtype.phys_info.drag;
          }
        }

#ifdef _DEBUG
      after_move:;
#endif
      }

      if (!f_attach_done) {
        AttachUpdateSubObjects(obj);
        f_attach_done = true;
      }

      if (!((ai_info->status_reg & AISR_MELEE) || (ai_info->flags & AIF_DISABLE_FIRING)))
        ai_fire(obj);
    } else {
      if (obj->movement_type == MT_WALKING && ai_info->animation_type == AS_DEATH) {
        vector mdir;
        bool f_moved;

        AIMoveTowardsPosition(obj, &obj->pos, 1.5f, false, &mdir, &f_moved);
        if (!f_moved) {
          AIMoveTowardsDir(obj, &mdir, 1.0f);
        }
      }
    }
  }

  if (!f_attach_done) {
    AttachUpdateSubObjects(obj);
    f_attach_done = true;
  }

  if (obj->movement_type == MT_WALKING)
    ai_walker_stuff(obj);

  // Animation state changes based on current level of awareness
  if (obj->control_type == CT_AI)
    do_awareness_based_anim_stuff(obj);

  // Decrease awareness
  if (obj->control_type == CT_AI)
    ai_decrease_awareness(obj);

  if (obj->ai_info->awareness > AWARE_BARELY && obj->ai_info->target_handle == Player_object->handle &&
      (obj->ai_info->last_see_target_time + (CHECK_VIS_INFREQUENTLY_INTERVAL * 2.0f)) >= Gametime &&
      (obj->ai_info->last_hear_target_time + (CHECK_VIS_INFREQUENTLY_INTERVAL * 2.0f)) >= Gametime &&
      obj->parent_handle != Player_object->handle) {
    AI_NumHostileAlert++;
  }

  if ((Game_mode & GM_MULTI) && (Netgame.local_role == LR_SERVER)) {
    if ((multi_saved_wb_firing != obj->ai_info->last_special_wb_firing) ||
        (multi_saved_weapon_flags != obj->weapon_fire_flags)) {
      MultiSendAiWeaponFlags(obj, obj->weapon_fire_flags, obj->ai_info->last_special_wb_firing);
    }
  }

}

void AIFrameAll(void) {
  int i;

  if ((Game_mode & GM_MULTI) && (Netgame.local_role == LR_CLIENT))
    return;

  // Currently, -- chrishack -- In multiplayer, all robots are aware.
  if (Game_mode & GM_MULTI) {
    for (i = 0; i <= Highest_object_index; i++) {
      if (Objects[i].ai_info) {
        AINotify(&Objects[i], AIN_PLAYER_SEES_YOU, NULL);
      }
    }
  } else {
    for (i = 0; i < AI_NumRendered; i++) {
      AINotify(&Objects[AI_RenderedList[i]], AIN_PLAYER_SEES_YOU, NULL);
    }
  }
}

void AIPowerSwitch(object *obj, bool f_on) {
  ai_frame *ai_info = obj->ai_info;
  if (obj->control_type != CT_AI)
    return;

  if (f_on)
    ai_info->flags &= (~AIF_DISABLED);
  else
    ai_info->flags |= AIF_DISABLED;

  poly_model *parent_pm = &Poly_models[obj->rtype.pobj_info.model_num];
  int i;

  if (!obj->attach_children)
    return;

  for (i = 0; i < parent_pm->n_attach; i++) {
    object *child;

    if ((child = ObjGet(obj->attach_children[i])) != NULL) {
      AIPowerSwitch(child, f_on);
    }
  }
}

int AIFindRoomWithFlag(object *obj, int flag) {
  int cur_room = obj->roomnum;
  float best_dist = 0.0f;
  int best_room = -1;
  int i;

  for (i = 0; i <= Highest_room_index; i++) {
    if ((Rooms[i].used) && (Rooms[i].flags & flag)) {
      float cur_dist;

      if (BOA_ComputeMinDist(obj->roomnum, i, 0.0f, &cur_dist, NULL)) {
        if (best_room == -1 || cur_dist < best_dist) {
          bool f_path_exists = AIFindAltPath(obj, cur_room, i, &cur_dist);

          if (f_path_exists && (best_room == -1 || cur_dist < best_dist)) {
            best_dist = cur_dist;
            best_room = i;
          }
        }
      }
    }
  }

  return best_room;
}

bool AIFindHidePos(object *hide_obj, object *view_obj, vector *hpos, int *hroom, float max_hide_time) { return false; }

object *AIFindObjOfType(object *obj, int type, int id, bool f_ignore_init_room, int parent_handle) {
  int cur_room = obj->roomnum;
  float best_dist = 0.0f;
  object *best_obj = NULL;
  int i;
  int my_obj_index = OBJNUM(obj);

  for (i = 0; i <= Highest_object_index; i++) {
    if ((Objects[i].type == type || (type == OBJ_ROBOT && Objects[i].type == OBJ_BUILDING)) && i != my_obj_index) {
      float cur_dist;

      if (f_ignore_init_room && (Objects[i].roomnum == obj->roomnum))
        continue;

      if (id != -1 && id != Objects[i].id)
        continue;

      // Allow us to find a players powerups
      if (parent_handle != OBJECT_HANDLE_NONE && parent_handle != Objects[i].parent_handle)
        continue;

      // Invisible powerups
      if (Objects[i].render_type == RT_NONE)
        continue;

      // Dying robots, other non-active robots
      if (Objects[i].type == OBJ_ROBOT && Objects[i].control_type != CT_AI)
        continue;

      // Robots that don't shoot
      poly_model *pm = &Poly_models[Objects[i].rtype.pobj_info.model_num];
      if (Objects[i].type == OBJ_ROBOT && pm->num_wbs == 0)
        continue;

      // cameras
      if (Objects[i].type == OBJ_ROBOT && pm->num_wbs == 1 && Object_info[Objects[i].id].static_wb[0].num_masks == 1 &&
          Object_info[Objects[i].id].static_wb[0].gp_fire_masks[0] == 0)
        continue;

      if (BOA_ComputeMinDist(obj->roomnum, Objects[i].roomnum, 0.0f, &cur_dist, NULL)) {
        if (best_obj == NULL || cur_dist < best_dist) {
          bool f_path_exists = AIFindAltPath(obj, cur_room, Objects[i].roomnum, &cur_dist);

          if (f_path_exists && (best_obj == NULL || cur_dist < best_dist)) {
            best_dist = cur_dist;
            best_obj = &Objects[i];
          }
        }
      }
    }
  }

  return best_obj;
}

int AIMakeNextRoomList(int roomnum, int *next_rooms, int max_rooms) {
  int num_next_rooms = 0;
  int i, j;
  int croom;

  if (!ROOMNUM_OUTSIDE(roomnum) && roomnum <= Highest_room_index) {
    for (i = 0; i < Rooms[roomnum].num_portals; i++) {
      bool f_found = false;

      if (Rooms[roomnum].portals[i].croom >= 0) {
        if (Rooms[Rooms[roomnum].portals[i].croom].flags & RF_EXTERNAL) {
          croom = Highest_room_index +
                  TERRAIN_REGION(GetTerrainRoomFromPos(
                      &Rooms[Rooms[roomnum].portals[i].croom].portals[Rooms[roomnum].portals[i].cportal].path_pnt)) +
                  1;
        } else {
          croom = Rooms[roomnum].portals[i].croom;
        }

        for (j = 0; j < num_next_rooms; j++) {
          if (next_rooms[j] == croom) {
            f_found = true;
            break;
          }
        }

        if (!f_found) {
          // If you hit assert, get chris -- make constant larger
          ASSERT(num_next_rooms < max_rooms);

          ASSERT((croom >= 0 && croom <= Highest_room_index + 8) ||
                 (ROOMNUM_OUTSIDE(croom) && CELLNUM(roomnum) > 0 && CELLNUM(roomnum) < TERRAIN_WIDTH * TERRAIN_DEPTH));

          next_rooms[num_next_rooms] = croom;
          num_next_rooms++;
        }
      }
    }
  } else {
    int t_index;

    if (BOA_num_terrain_regions == 0) {
      return 0;
    }

    if (roomnum > Highest_room_index && roomnum <= Highest_room_index + 8) {
      t_index = roomnum - Highest_room_index - 1;
    } else {
      t_index = TERRAIN_REGION(roomnum);
    }

    ASSERT(t_index >= 0 && t_index < BOA_num_terrain_regions);

    for (i = 0; i < BOA_num_connect[t_index]; i++) {
      bool f_found = false;
      croom = BOA_connect[t_index][i].roomnum;

      for (j = 0; j < num_next_rooms; j++) {
        if (next_rooms[j] == croom) {
          f_found = true;
          break;
        }
      }

      if (!f_found) {
        // If you hit assert, get chris -- make constant larger
        ASSERT(num_next_rooms < max_rooms);
        next_rooms[num_next_rooms++] = croom;
      }
    }
  }

  return num_next_rooms;
}
