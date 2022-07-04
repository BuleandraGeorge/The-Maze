<h1 style="text-align:center">THE MAZE</h1>

<p style="font-size:1.5rem">
    The creation of the game started with an asignment at my university where I had to demonstrate
    inherintace, downcasting and upcasting. During the development more ideas emerged and I gave it a second
    look and enriched it with more features
</p>
<h2> The goal</h2>
<p> To win you need to reach the portal while avoiding the bullets shooted by the turrets around the map.</p>

<h2>UX & UI</h2>
<p>
When you run the game you'll land up in the menu of the game which offers you 4 ways to go:
    <ul>
        <li>Play: brings you on map </li>
        <li>Change Map: offers you the possibility to change the map</li>
        <li>Hall of Fame: shows all the highscores </li>
        <li>Exit: exits the game</li>
    </ul>
    The design of the menu is minimalist having only text.
</p>
<p>
    During the game you can pause it or go to main menu by pressing "ESC" and selecting one of the option in the pause
    menu with up and down arrows and space which acts as enter.
</p>
<p>
    If you finish the map in a record number of attemps (smaller is better) you can save it with your name and see it in the Hall of Fame. All the highscore are saved after exitting the game.
</p>
<p>
    The game also offers the possibility not only to choose between multiple maps but to create your own maps too.(More Details in Maps Tutorial)
</p>
<p>You've got only one life to escape the map, if you die you can play again and a new attemp is registered. You'll start at the beginning of the map</p>

<h2>Features</h2>
<ul>
    <li>Menu</li>
    <li>Map creation</li>
    <li>Highscore and names</li>
    <li>Scores are saved after exitting the game</li>
</ul>
<h3>Features left to implement</h3>
<p>I would like to add the posibility the create the map in the game using drag and drop actions</p>
<p>A more detailed costumisation of the turrets, like number of bullets, delay between patterns</p>
<p>To add mistery boxes with coins and to add a score based on retriving that mistery boxes</p>
<p>Trap floor which triggers when passed over</p>
<p>Lives</p>

<h2>Technologies Used</h2>
<p>
    <ul>
        <li>Programming language: C++;</li>
        <li>SFML library</li>
    </ul>
</p>
<h2>Testing</h2>
<p>
    During the development of game I found different bugs like:
    <ul>
        <li>the user could get inside the wall using the right combination of keys; fixed.</li>
        <li>the program crashes for a wrong map structure:not fixed</li>
    </ul>
    The testing is minimalist and done by playing the game.
</p>
<h2>Deployment</h2>
<p>
    To run the game in the current format you need to:
    <ul>
        <li>
            Download SFML 2.5.1 from here <a href="https://www.sfml-dev.org/download/sfml/2.5.1/">SFML 2.5.1 Download</a>
        </li>
        <li>Add SFML 2.5.1 in "Project Files" folder </li>
        <li>Run Cmake with destination in included "Build" folder</li>
    </ul>
</p>
<h2>Maps Tutorial</h2>
<p>
    In order to created a map you need a csv file. The name of the file it will be the name of the map.
</p>
<p>
    The commands are:
    <ul>
        <li>w - for defining a wall square </li>
        <li>f - for defining a floor square</li>
        <li>ox - for defining the player where x is the facing direction</li>
        <li>px - for defining a turret which fires 3 bullets every couple seconds, where x is the direction of shooting</li>
        <li>txy -  for defining a turret which fires when a trigger is passed by the player, where x is the shooting direction and y is the id of the trigger</li>
        <li>my -  for defining a trigger where y is the turret id which triggers</li>
        <li>z -  for defining a square of the portal </li>
        <li>s -  for defining the area where the number of attemps will be displayed, you need to declare 3 consecutive fields with this value horizontally </li>
    </ul>
    <span>For x the valid values are :</span>
    <ul>
        <li>l - for declaring the orientation to left</li>
        <li>r - right</li>
        <li>d - down</li>
        <li>u - up</li>
    </ul>
    <p> y - which is used to declare the linking between a turret and its trigger takes values between 0 and 9. Eg: tr0 and m0, commands for declaring trigger turret orientated to right with id 0 and it's trigger </p>
    <p>In the csv file you need to fill up every single field with one of the commands from above to discribe the map</p>
    <p>You need to end up with a table of 12 rows by 24 columns which has every field filled up with one of the commands</p>
    <p>You need to add the file in the maps folder .\Project\Build\Maps  << here </p>
    <p>Tips: you can use an existing map as a guide or a boilerplate for your new map</p>


</p>

