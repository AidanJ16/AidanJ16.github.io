package edu.illinois.cs.cs124.ay2021.mp.activities

import android.annotation.SuppressLint
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import androidx.databinding.DataBindingUtil
import edu.illinois.cs.cs124.ay2021.mp.R
import edu.illinois.cs.cs124.ay2021.mp.databinding.ActivityRestaurantBinding
import edu.illinois.cs.cs124.ay2021.mp.network.Client

class RestaurantActivity : AppCompatActivity() {
    // Binding to the layout defined in activity_main.xml
    private lateinit var binding: ActivityRestaurantBinding
    @SuppressLint("SetTextI18n")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        var restaurantID = intent.extras!!.get("id") as String
        var res = Client.restaurantMap[restaurantID]
        var resCuisine = res!!.cuisine
        var resName = res!!.name
        var getRelated = Client.rel.getRelatedInOrder(restaurantID)
        var getConnected = Client.rel.getConnectedTo(restaurantID)
        println(getConnected.size)
        println(resName + resCuisine)
        binding = DataBindingUtil.setContentView(this, R.layout.activity_restaurant)
        binding.name.text = resName + " " + resCuisine
        if (getConnected.isEmpty() && getRelated.isEmpty()) {
            binding.related.text = null
            binding.size.text = 0.toString()
        } else if (getConnected.isEmpty()){
            binding.related.text = getRelated.first().name
            binding.size.text = 0.toString()
        } else if (getRelated.isEmpty()) {
            binding.related.text = null
            binding.size.text = getConnected.size.toString()
        } else {
            binding.related.text = getRelated.first().name
            binding.size.text = getConnected.size.toString()
        }
    }
}