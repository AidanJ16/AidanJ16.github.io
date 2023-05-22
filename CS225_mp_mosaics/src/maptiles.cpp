/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include <vector>
#include "maptiles.h"
using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    // create canvas based on source image
    MosaicCanvas * ret = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    // need map to find tile from point
    std::map<Point<3>, TileImage *> maps;
    // need vector to hold all tiles average points
    std::vector<Point<3>> vect;
    // populate map and vector
    for(unsigned i = 0; i < theTiles.size(); i++) {
        LUVAPixel pix = theTiles[i].getAverageColor();
        Point<3> point = convertToXYZ(pix);
        maps.insert({point, &(theTiles[i])});
        vect.push_back(point);
    }
    KDTree<3> avg_tree(vect);
    // add tiles
    // iterate for all rows and columns of source image
    // attain current regions avg color and convert to point
    // use nearest neighbor to find point in vector closest
    // grab corresponding tile from point returned
    // set tile and continue
    for(int i = 0; i < theSource.getRows(); i++) {
        for(int j =0; j < theSource.getColumns(); j++) {
            LUVAPixel avg_reg_pix = theSource.getRegionColor(i, j);
            Point<3> to_find = convertToXYZ(avg_reg_pix);
            Point<3> best = avg_tree.findNearestNeighbor(to_find);

            TileImage * tile_send = maps[best];
            ret->setTile(i, j, tile_send);
        }
    }


    // return populated canvas
    return ret;
}

