// ktlint-disable filename

package edu.illinois.cs.cs124.ay2021.mp.models

import com.github.wrdlbrnft.sortedlistadapter.SortedListAdapter

/*
 * Model storing information about a restaurant retrieved from the restaurant server.
 *
 * You will need to understand some of the code in this file and make changes starting with MP1.
 *
 */
@Suppress("unused")
class Restaurant(val name: String, val cuisine: String, val id: String) : SortedListAdapter.ViewModel {
    constructor() : this("", "", "")

    companion object {
        /*
         * Function to compare Restaurant instances by name.
         * Currently this does not work, but you will need to implement it correctly for MP1.
         * Comparator is like Comparable, except it defines one possible ordering, not a canonical ordering for a class,
         * and so is implemented as a separate method rather than directly by the class as is done with Comparable.
         */
        val SORT_BY_NAME = Comparator<Restaurant> { restaurant1, restaurant2 ->
            restaurant1.name.compareTo(restaurant2.name)
        }
    }

    // You should not need to modify this code, which is used by the list adapter component
    override fun <T : Any?> isSameModelAs(model: T) = this == model

    // You should not need to modify this code, which is used by the list adapter component
    override fun <T : Any?> isContentTheSameAs(model: T) = this == model

    override fun toString(): String = name
    override fun equals(other: Any?) = when {
        javaClass != other?.javaClass -> false
        else -> {
            other as Restaurant
            id == other.id
        }
    }
    override fun hashCode() = id.hashCode()
}

fun List<Restaurant>.search(input: String): List<Restaurant> {
    val trimmed = input.trim()
    val toReturn = mutableListOf<Restaurant>()
    if (input == null || trimmed == "") {
        val copy = ArrayList<Restaurant>(this)
        return copy
    }
    val lower = input.trim().lowercase()
    println(lower)
    val cuisines = mutableSetOf<String>()
    for (restaurant in this) {
        cuisines.add(restaurant.cuisine.lowercase())
    }
    if (cuisines.contains(lower)) {
        for (restaurant in this) {
            if (restaurant.cuisine.lowercase() == lower) {
                toReturn.add(restaurant)
            }
        }
    } else {
        for (restaurant in this) {
            if (restaurant.cuisine.lowercase().contains(lower) || restaurant.name.lowercase().contains(lower)) {
                toReturn.add(restaurant)
            }
        }
    }
    for (restaurant in toReturn) {
        println(restaurant.name + "===" + restaurant.name)
    }
    return toReturn
}

// MP2 Part 1: Add information to my preference
class Preference(val id: String, val restaurantIDs: List<String>) {
    constructor() : this("", emptyList())
}

// MP2 Part 4: Related Restaurants model
class RelatedRestaurants(restaurants: List<Restaurant>, preferences: List<Preference>) {
    private val restaurantRMap: MutableMap<String, MutableMap<String, Int>> = mutableMapOf()
    private var idList = arrayListOf<String>()
    private var resMap: MutableMap<String, Restaurant> = mutableMapOf()
    private var resSet: MutableSet<Restaurant> = mutableSetOf()
    init {
        for (r in restaurants) {
            idList.add(r.id)
            resMap[r.id] = r
            resSet.add(r)
        }
        for (p in preferences) {
            var restaurantID = p.restaurantIDs
            for (id1 in restaurantID) {
                for (id2 in restaurantID) {
                    if (id1 != id2) {
                        if (idList.contains(id1) && idList.contains(id2)) {
                            if (restaurantRMap.containsKey(id1)) {
                                if (restaurantRMap[id1]!!.containsKey(id2)) {
                                    var current = restaurantRMap[id1]!![id2]!!
                                    restaurantRMap[id1]!!.replace(id2, current + 1)
                                } else {
                                    restaurantRMap[id1]!!.put(id2, 1)
                                }
                            } else {
                                var map = HashMap<String, Int>()
                                map.put(id2, 1)
                                restaurantRMap.put(id1, map)
                            }
                        }
                    }
                }
            }
        }
    }
    fun getRelated(from: String): Map<String, Int> {
        return restaurantRMap[from] ?: mapOf()
    }
    fun getRelatedInOrder(from: String): List<Restaurant> {
        // validate string
        // call getRelated
        // Convert string keys to List<Restaurant>
        // Sort the list
        require(from in resMap.keys)
        var rMap = getRelated(from)
        var listRelated = mutableListOf<Restaurant>()
        for ((k, v) in rMap) {
            listRelated.add(resMap[k]!!)
        }
        for (r in listRelated) {
            assert(r.id != null)
        }
        var sorted = listRelated!!.sortedBy { it -> it.name }.sortedByDescending { it -> rMap[it.id]!! }
        return sorted
    }
    fun getConnectedTo(from: String): Set<Restaurant> {
        require(from in resMap.keys)
        var returnSet = mutableSetOf<Restaurant>()
        var stringSet = mutableSetOf<String>()
        helper(from, stringSet, 2)
        println(stringSet)
        for (string in stringSet) {
            if (resMap.keys.contains(string)) {
                returnSet.add(resMap[string]!!)
            }
        }
        returnSet.remove(resMap[from])
        return returnSet
    }
    private fun helper(resID: String, seen: MutableSet<String>, distance: Int) {
        require(resID in resMap.keys)
        var rMap = getRelated(resID)
        seen += resID
        if (distance == 0) {
            return
        }
        for (neighbor in rMap.keys) {
            try {
                if (rMap[neighbor]!! > 1) {
                    helper(neighbor, seen, distance - 1)
                }
            } catch (e: NullPointerException) {
                println("Safe")
            }
        }
    }
}