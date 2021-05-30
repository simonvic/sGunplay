# sGunplay

<p align="center">
        <img src="https://imgur.com/KET237w.png" width="50%">
        <br>
		<img src="https://img.shields.io/github/v/tag/simonvic/sGunplay?color=F0544C&label=latest%20stable%20release&style=for-the-badge">
        <br>
		<img src="https://img.shields.io/github/license/simonvic/sGunplay?color=F0544C&style=flat-square">
</p>

# What is **sGunplay**

**sGunplay** is the second module of the much more ambitious *sUDE* project. 
Its main goal is to give a slightly more hardcore and different experience, but carefully balanced to don't make it feel much different from the vanilla game, while improving the PvP (and PvE) in many aspect.

# **Key** aspects and **reasons** of the mod

The current DayZ gunplay feels too fast and arcade, with sGunplay I try to fix that problem (Keep in mind that it still lacks some core features, therefore it doesn't completely represent the final vision I have for the gunplay)
- sGunplay incentives a more thought-out and slightly slower PvP.

- Running and shooting, rushing enemies while hipfiring and other things that make the game feel like an arcade-type shooter, are less rewarding

- Your inventory now plays a big role in recoil control, precision and weapon handling. Think twice what weapon to use and what stuff you really need to bring with you when going to PvP hot zones (the sClothing module, with layered clothing, redesigned inventory slots and more, will majorly modify this aspect, so stay tuned)

- A more dynamic and always different PvP, thanks to the many features added.

# Differences from vanilla DayZ

## Less arcadeish gameplay

The PvP/PvE has been "slowed" down in many aspect (more with the future Movement update) 
- Slower AimingDownSight (ADS) time, less snappy, robotic and arcadey animation (procedural ADS times will come with future updates)

- "Focus" mechanic. Holding your breath will help you focus while in ADS, giving less sway and more precision. The focus speed will change based on the player stance (more to come in the future)
- Reduced FieldOfView while aiming ADS, which combined with the new "focus" mechanic incentivate the player to think twice before shooting

---

## Procedural weapon **inertia**

No more insane 360° flicks with a 5kg weapon, thanks to the new inertia system.
- It's completely dynamic, based on:
  - Weapon weight
  - Inventory weight
  - Player stance (erect, crouched, prone)
  - Movement speed
  - Hipfire (inertia will be much more visible while hipfiring)
  - Player injury state
  - *... more to come with the SoftSkills module*

---

## Procedural weapon **recoil**

The weapon recoil system has been remade from scratch, which allowed me to make it more realistic, visually more appealing and more dynamic

Weapon recoils are procedurally created based on many variables:
  - Attachments (more to come in the future)
  - Character strength (softskill you see when you open the inventory)
  - Inventory weight (no more "360 midair noscope" while carrying 3 weapons and 50kg of stuff on your back)
  - Stance (erect, crouched, prone)
  - Movement (you'll be able to control recoil much better while standing still)
  - Hipfire (while hipfiring you won't be able to control the recoil very easily)
  - *...more to come with the softskills module*

All weapon recoils have been carefully tweaked one by one, to find the perfect balance between usability and fire power

---

## Completely reworked player **camera**

- Deadzone! It is also possible to tweak the deadzone strength as you wish
- The camera is not "tied" to the weapon anymore
- "PictureInPicture" (PiP) emulation. The mangifying optic lens effect has received a major overhaul to better emulate the dual render technic used by games like Insurgency or EscapeFromTarkov. And it also is 100% compatible deadzone!
- Customizable DepthOfField while ADS
- It's possible to Freelook while ADS (only with ironsights and non-magnifying optics)
- It's possible to visually inspect the weapon (only with ironsights and non-magnifying optics)

---

## Dynamic **crosshair**

The dynamic crosshair is inspired from the .62 version of DayZ. Such crosshair would help you while hipfiring, showing you where your gun is point at; so it will be much easier to understand if you're shooting a tree or the enemy behind it .

- It can be enabled/disabled from the menu settings
- Servers can decide to disable it by toggling the crosshair options in the serverDZ.cfg

---

## Improved **sway** and **stamina** drain

- The weapon sway (caused by the breathing) is a lot more predictable and much easier to control (without crazy spasm from your character).
- Holding your breath will drain your stamina a bit slower than vanilla. This has been done to compensate the "time" you need to focus, while also making the timing more plausible, gameplay and realism wise

---

<br>
<br>

# __sUDE discord__ server

Join the discord server for more info, news and preview of new additions to the mods
<p align="center">
    <a style="margin: 0 10px" href = "https://discord.gg/HEtYJHUyE5">
        <img style="margin: 0 10px" src="https://img.shields.io/badge/Discord-sUDE-F0544C?logo=Discord&style=social">
    </a>
</p>


# Contact me
<h2 align="center">Found a bug or want to give a suggestion? Feel free to contact me!</h2>
<p align="center">
    <a style="margin: 0 10px" href = "mailto: simonvic.dev@gmail.com">
        <img src="https://img.shields.io/badge/Email-simonvic.dev%40gmail.com-F0544C?style=social&logo=data:image/png;base64,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&logoColor=F0544C">
    </a>
    <br>
    <a style="margin: 0 10px" href="https://matrix.to/#/@simonvic:matrix.org">
        <img src="https://img.shields.io/badge/Matrix-%40simonvic%3Amatrix%3Aorg-F0544C?logo=element&style=social">
    </a>
    <br>
    <img style="margin: 0 10px" src="https://img.shields.io/badge/Discord-simonvic%239804-F0544C?logo=Discord&style=social">
    <br>
    <a style="margin: 0 10px" href="https://twitter.com/_simonvic_">
        <img src="https://img.shields.io/badge/Twitter-%40simonvic-F0544C?logo=twitter&style=social">
    </a>
</p>

---

<h3 align="center" >Buy me a coffee :)</h3>
<p align="center">
    <img width="40px" src="https://i.imgur.com/e3kk9J4.png">
    <a href = "https://paypal.me/simonvic">
        <img src="https://img.shields.io/badge/Paypal-donate-F0544C?style=for-the-badge&logo=paypal&logoColor=F0544C">
    </a>
</p>