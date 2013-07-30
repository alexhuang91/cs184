# API Documentation

Staging URL:
  http://chatsportslabs.com:4567/

Production URL:
  http://api.chatsports.com

Example request(this does not use your api key, it uses another one of ours):

http://chatsportslabs.com:4567/sites/search/giant?key=YOUR_API_KEY&signature=67f2d4679abd856c40fa8dd5554a8bb0

## We use [JSend-style](http://labs.omniti.com/labs/jsend) responses:
- ### Successful Response:
      { "status" : "success",
          "data" : { "session_key" : <key>,
                            "user" : {       "id" : "<user_id>",
                                       "username" : "<username>" } } }

- #### Error Response:
      {  "status" : "error",
           "code" : "SomeError"
        "message" : "A title is required"
      }


Note: If a field doesn't exist, there is no guarantee that it will be included in the JSON.

## Sign in, registration, password
- ### Sign in email
  - #### Request
    ``` /user/email/login ```

    ##### Params:
          email=<string>
          password=<string>

  - #### Success Response
    ```json 
       {
        "status" : "success"
          "data" : {
                     "session" : {
                                   "session_key" : "<integer>"
                                 } 
                        "user" : {
                                              "id" : "<integer>"
                                    "date_created" : "<unix_time>"
                                    "date_updated" : "<unix_time>"
                                        "username" : "<string>"
                                           "email" : "<string>"
                                      "first_name" : "<string>"
                                       "last_name" : "<string>"
                                          "fb_uid" : "<integer>"
                                     "fb_username" : "<string>"
                                  }
                   }
         } ```

  - #### Errors:
        AuthenticationError
----

- ### Sign up email
  - #### Request
    ``` /user/email/register ```

    ##### Params:
          email=<string>
          password=<string>

  - #### Response
        JSON { "status" : "success"
                 "data" : { "session" : {  "session_key" : "<integer>" } 
                               "user" : {           "id" : "<integer>"
                                          "date_created" : "<unix_time>"
                                          "date_updated" : "<unix_time>"
                                              "username" : "<string>"
                                                 "email" : "<string>"
                                            "first_name" : "<string>"
                                             "last_name" : "<string>"
                                                "fb_uid" : "<integer>"
                                           "fb_username" : "<string>" } } }

  - #### Errors:
        DuplicateEmailError, InvalidInputError


- ### Sign in facebook  ([SSO How To](https://developers.facebook.com/blog/post/640/))
  - #### Request
    ``` /user/facebook/login ```

  - #### Response
        JSON { "status" : "success"
                 "data" : { "session" : {  "session_key" : "<integer>" } 
                               "user" : {           "id" : "<integer>"
                                          "date_created" : "<unix_time>"
                                          "date_updated" : "<unix_time>"
                                              "username" : "<string>"
                                                 "email" : "<string>"
                                            "first_name" : "<string>"
                                             "last_name" : "<string>"
                                                "fb_uid" : "<integer>"
                                           "fb_username" : "<string>" } } }

  - #### Errors
    none


- ### Sign up facebook
  - #### Request 
    ``` /user/facebook/register ```
  
  - #### Response
        JSON { "status" : "success"
                 "data" : { "session" : {  "session_key" : "<integer>" } 
                               "user" : {           "id" : "<integer>"
                                          "date_created" : "<unix_time>"
                                          "date_updated" : "<unix_time>"
                                              "username" : "<string>"
                                                 "email" : "<string>"
                                            "first_name" : "<string>"
                                             "last_name" : "<string>"
                                                "fb_uid" : "<integer>"
                                           "fb_username" : "<string>" } } }


  - #### Errors
    none


- ### Link facebook
  - #### Request
    ``` /user/facebook/link ```

  - #### Response
        JSON { "status" : "success"
                 "data" : { "user" : {           "id" : "<integer>"
                                       "date_created" : "<unix_time>"
                                       "date_updated" : "<unix_time>"
                                           "username" : "<string>"
                                              "email" : "<string>"
                                         "first_name" : "<string>"
                                          "last_name" : "<string>"
                                             "fb_uid" : "<integer>"
                                        "fb_username" : "<string>" } } }
  

- ### Link Email
  - #### Request
    ``` /user/email/link ```
    
  - #### Response
        JSON { "status" : "success"
                 "data" : { "user" : {           "id" : "<integer>"
                                       "date_created" : "<unix_time>"
                                       "date_updated" : "<unix_time>"
                                           "username" : "<string>"
                                              "email" : "<string>"
                                         "first_name" : "<string>"
                                          "last_name" : "<string>"
                                             "fb_uid" : "<integer>"
                                        "fb_username" : "<string>" } } }

- ### Change Username
  - #### Request
  ``` /user/username/change ```
    
  - #### Response
        JSON { "status" : "success"
                 "data" : { "user" : {           "id" : "<integer>"
                                       "date_created" : "<unix_time>"
                                       "date_updated" : "<unix_time>"
                                           "username" : "<string>"
                                              "email" : "<string>"
                                         "first_name" : "<string>"
                                          "last_name" : "<string>"
                                             "fb_uid" : "<integer>"
                                        "fb_username" : "<string>" } } }
  - #### Errors
        UsernameTakenError

- ### Change password
  - #### Request
    ``` /user/password/change ```

  - #### Response
    ```json
         { "status" : "success"
                 "data" : { "user" : {           "id" : "<integer>"
                                       "date_created" : "<unix_time>"
                                       "date_updated" : "<unix_time>"
                                           "username" : "<string>"
                                              "email" : "<string>"
                                         "first_name" : "<string>"
                                          "last_name" : "<string>"
                                             "fb_uid" : "<integer>"
                                        "fb_username" : "<string>" } } } ```

- ### Forgot password
  - #### Request
    ``` /user/password/reset ```

  - #### Response
    TBD

## Teams
### Request a team
``` /teams/:id ```

### Request teams
``` /teams ```

### Follow/unfollow teams
``` /user/follow/teams ```

``` /user/unfollow/teams ```


### Trending stories
``` /news/trending ```

### Search bar
``` /news/search ```

``` /writers/search ```

``` /users/search/email ```

``` /users/search/username ```


## News
### Display content (UIWebView, maybe Readability? [flipboard], etc)
        (SEE GITHUB readme)

## Writers
### Follow/unfollow writers
``` /user/follow/writers ```

``` /user/unfollow/writers ```

## Social
### Sharing - Facebook / twitter
``` /user/<resource type>/share/facebook ```

``` /user/<resource type>/share/twitter ```

### Vote in polls
``` /user/vote/polls ```

### User profile (unique page - i,e. chatsports.com/james - my actions/activity)
``` /user/view/profile/<id> ```


### Settings
        App Settings and User Preferences
``` /user/settings/change ```

### Notifications
        Interface with Tornado
``` /user/notifications ```

### GPS location - (for local news)
``` /teams/location/longitude/<longitude>/latitude/<latitude> ```

``` /news/location/longitude/<longitude>/latitude/<latitude> ```

### Errors
- ####  Authentication Error
- ####  Invalid Request
- ####  Invalid Input Error
