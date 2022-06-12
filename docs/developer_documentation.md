Introduction
============

The City Building Series made by British developer *Impressions Games* is a fantastic, if relatively simple, series of city management simulator games taking place in various Antiquity-era settings. The unique appeal of this series are the mythological elements, particularly in the Greek-themed installment.

Although the games still run well on modern platforms, and are a hallmark of quality in terms of the (lack of) number of bugs, there is no free/libre and open-source option available for the entire series, and the game engines themselves are difficult to extend; the Adventure Editors are limited and can easily produce custom adventures that are frustrating, and unplayable; there is no direct support for user mods; custom assets such as skin packs are very difficult if not impossible.

This project, *OpenImpressions*, aims to provide a **mostly faithful** implementation of some of the games in the City Building Series. The primary focus is to implement the functionality of the Greek-themed installment, and then expand to the other games in the series. As such, the following design document and note sections are largely based off of *Zeus*. Whereas other projects, such as Bianca van Schaik's excellent [Julius](https://github.com/bvschaik/julius), seek to **faithfully** implement the experience of only Caesar III, *OpenImpressions* yearns to handle all of *Pharaoh*, *Caesar III*, *Zeus: Master of Olympus*, and expansions if applicable, in one project.

As well as providing an alternative to the original games, this project will expand upon the Greek-themed installment with an expansion: *Hades: Master of the Underworld*. This expansion will feature new resources; walkers and buildings; Gods, heroes, and monsters; and most enticingly, newer and polished mechanics.

Terminology
===========

- *Caesar*: the 1998 game *Caesar III*.
- *Pharaoh*: the 1999 game *Pharaoh* and its 2000 expansion, *Cleopatra: Queen of the Nile*
- *Zeus*: the fifth title in the City Building Series, *Zeus: Master of Olympus* and its expansion *Poseidon: Master of Atlantis*. Unless explicitly noted with *Zeus* or *Poseidon*, 
- *Hades*: the planned expansion intended to showcase the new features in the *OpenImpressions* engine.
- *Emperor*: the six title in the City Building Series, *Emperor: Rise of the Middle Kingdom*.

City Maps
=========

**City Maps** are where most of the game takes place. They have the following properties:

	Scrub type (temperate or tropical)

	8 fishing points
	8 urchin points

	8 Disaster points
	3 Landslide points

	8 Land invasion points
	8 Sea invasion points
	3 Disembark points

Note that in the original *Zeus/Poseidon*, there is a restriction on food types, total allowable resources, et cetera. These restrictions are removed in *Hades*.

Tiles
-----

A **tile** is a single cell in a City Map, which has the following properties:

	Name           Type and potential (mutually exclusive) values

	ground         {water, land, beach, marsh, shore, meadow, igneous, marble, blackmarble}
	overlay        {none, grass, cliff, bigcliff}
	orientation    `[0-255]`, see below
	height
	
Tiles are referred to by their `x,y` coordinate, with the coordinates matching the original game engine (TODO: explain what that means. i think 0,0 is top left?)

### Tile types/features still missing

- earthquake
- trees

### Notes

An interesting observation: in the Adventure Editor, place some grass on land tiles, then place rocks. If you use the grass tool again, the rocks disappear and the grass level is increased as though it were a regular land tile. Also, place a quarry overtop some grass, then delete it; the underlying grass is preserved. These examples demonstrate that grass is stored independently.

`marble` and `blackmarble` ground types are only walkable so long as they have not been mined. Also, quarries have "edge tiles" -- tiles that cannot be built on, and can never be mined. These are represented by certain values for `orientation`.

There seems to be a repeating pattern with "edge tiles": certain ground types transition from one to another, with the tile in-between representing some sort of "edge": a coastline, the edge of a quarry, et cetera. The in-game logic treats edges differently:

- structures cannot be placed on edge tiles, except...
- certain structures (water crossings, docks, etc.) have parts of them that are required to be placed on edge tiles
- units generally cannot enter edge tiles, with the exceptions being the land/beach and land/quarry edges

Tile Orientation
----------------

The `orientation` of a tile determines several properties, dependent on the overlay. The orientation always influences what the file looks like.

- `water` tiles reflect sho


Tile Height and Cliffs
----------------------

Cliffs are caused by differences in tile height. The minimum height is zero, and the maximum height is high enough to create unplayable maps. In Zeus/Poseidon, cliffsides are limited to sizes of 1 or 2. One can design mountains and valleys with steeper sides, but the engine splits them into a one segment cliffside followed by a two segment cliffside, or vice versa. It may be desirable to generalise cliffsides in *OpenImpressions*.

One can do silly things within the Adventure Editor, such as draw a body of water over a mountain. The shoreline is influenced by water tiles "underneath" cliffsides, thus demonstrating that cliffsides are handled as an overlay.

The logic for drawing and handling cliffs appears to be as follows (please note this is by no means complete):

If a one segment cliffside is facing the camera, the tile "up" is treated as a "dead tile" with the top of the cliff as its graphic. The tile cannot be interacted with -- for example, placing a road build cursor on the "dead" tile causes it to clamp itself to the tile "down" from the cliffside.

The Adventure Editor automatically places landslide zones for some cliffsides with a height of 2 or greater, but how it determines whether and where to place these zones is still a mystery.


World Map
=========

background
list-of cities
list-of region labels
trade routes

Trade Routes
------------

has: start city, end city, list of points, type {land/sea}