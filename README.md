# less-scope

Less of a scope for Ubuntu Touch

## WHY?

["Because sometimes less is more"](https://unix.stackexchange.com/questions/81129/what-are-the-differences-between-most-more-and-less#81131).

Did you ever notice you opened an app although you **knew** it would not show you something new (because you've done so twice in the last 3 minutes)?

It seems seeing that app-icon on your app-scope just triggered an unconscious train of thoughts:

* *"Ooh! I know that icon!"*
* *"You can click on it!"*
* *"Sometimes I was fascinated by its content!"*
* *"So I'll click it and see if it brings me joy!"*
* *"Thumbs: move!"*
* *"Woooohooo it opens up!"*
* **-> THAT'S WHERE YOUR CONSCIOUSNESS NOTICES WHAT JUST HAPPENS <-**
* *"Nooooh. Nothing new :("* OR *"Yay new content. Let's waste some (more) time!!!!!!!!!!"*

The question is: is this what you want?

(BTW: It seems like something many content providers want... [Zeynep Tufekci](https://www.ted.com/talks/zeynep_tufekci_we_re_building_a_dystopia_just_to_make_people_click_on_ads) and [Tristan Harris](https://www.ted.com/talks/tristan_harris_the_manipulative_tricks_tech_companies_use_to_capture_your_attention) on the topic.)

Since you unconsciously started the app - before you even noticed it - what's there to do about?

**-> One approach would be to reduce the stimulus. Move the app-icon outside of your field of perception, i.e. make the app-drawer scope or any other news-displaying / attention-munching scope not your "home" screen.**

Since there are only content-providing scopes available at the moment (that's their purpose right?), this scope intends to be **less**. It just shows you a nice picture :) No news, no apps. You still have those - "only one swipe away". But not immediately ;)

## How to use it

1. Make it your "Home" scope ;)
2. Search for "info" for some info.

### Setting a "theme"

A "theme" consists of a picture, a title, a subtitle and a text.

1. Search for "all" to see all themes.
2. Go to the settings page.
3. Type the name of the theme ;)

*"[But I want to change the background-color / have a clock on the screen / ...](#anticipated-questions)"*

### Setting your own Picture / Title / Text

You can effectively create your own theme by customizing all the displayed entities.

#### Title / Subtitle / Text

1. Go to the settings page.
2. Type the text you want displayed.

**Note**: An empty "Subtitle" will be replaced by the current date.

This does not change the current theme - it changes only what's displayed!

#### Pictures

The scope can display a picture from your `~/Pictures` folder. The best aspect ratio is 9:16 or 10:16.

1. Go to the settings page.
2. Append the name of your picture. (The path `/home/phablet/Pictures/` should already be displayed.)

This does not change the current theme - it changes only what's displayed!

To revert to the picture displayed by the theme set the field to its default value: `/home/phablet/Pictures/` (**note the trailing slash**)

## Anticipated questions

(... I've not yet been asked.)

### I want to change the background-color / have a clock on the screen / ...

The scope API provides no too much options for customization.

Although it provides an option to set the background-colour, I have not yet figured out a way to do so at runtime.

### Does it connect to the internet?

Nope.

## Hack it!

Got some good idea to improve the scope? Go! ;)

### Build & install

The project is settup for use with Brian Douglas' `clickable`.

```bash
# 1. install `clickable`

# 2. get the code

git clone https://github.com/randomchars42/less-scope.git

cd less-scope

# 3. attach your ubuntu device

# 4. build & install
#    (the default actions are described in clickable.json)

clickable
```

### Note

I'm not a professional programmer and I taught myself C++ some 15 years ago with a book from the 90s. You may ask me why I wrote something the way I wrote it and I'll try and help. But it's mostly *"Because DuckDuckGo said so"* ;)

