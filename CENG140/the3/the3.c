#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_USER_CAPACITY 1000
#define DB_POST_CAPACITY 1000
#define USERNAME_MAX_LEN 100
#define POST_CONTENT_MAX_LEN 1000

typedef struct {
  int day;
  int month;
  int year;
} Date;

typedef struct Node {
  void *data;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct {
  int userId;
  char *username;
  Date *birthday;
  Node *followers_head;
  Node *followers_tail;
  int numOfFollowers;
  int numOfFollowing;
  int liked;
} User;

typedef struct {
  int postId;
  char *content;
  User *author;
  int likes;
} Post;

typedef struct Database {
  User users[DB_USER_CAPACITY];
  Post posts[DB_POST_CAPACITY];
} Database;

typedef struct Cache {
  int capacity;
  int size;
  Node *head;
  Node *tail;
} Cache;

void printUser(User *user);
void printPost(Post *post);
void printUserCache();
void printPostCache();
void printFollowersInReverse();

Node *createNode(void *data);
void appendToCache(Cache *cache, void *data);
void moveToFront(Cache *cache, Node *node);
void removeLast(Cache *cache);
void freeLinkedList(Node *head);

User *fetchUser(int userId);
Post *fetchPost(int postId);
void followUser(int followerId, int followedId);
void likePost(int userId, int postId);

Database db;
Cache userCache;
Cache postCache;
/*void data*/
void printUser(User *user) {
  printf("User: %d, Username: %s, Followers: %d, Following: %d, Liked: %d\n",
         user->userId, user->username, user->numOfFollowers,
         user->numOfFollowing, user->liked);
}

void printPost(Post *post) {
  printf("Post: %d, Author: %s, Likes: %d\n", post->postId,
         post->author->username, post->likes);
}

void printUserCache() {
    Node *trav = userCache.head;
    printf("UserCache:\n");
    while (trav)
    {
        printUser(trav->data);
        trav = trav->next;
    }
}

void printPostCache() {
    Node *trav = postCache.tail;
    printf("PostCache:\n");
    while (trav)
    {
        printPost(trav->data);
        trav = trav->prev;
    }
}

Node *createNode(void *data) { 
    Node *new = malloc(sizeof(Node));
    new->data = data;
    new->next = NULL;
    new->prev = NULL;
    
    return new;
}

void appendToCache(Cache *cache, void *data) { 
    Node *new = malloc(sizeof(Node));
    new->data = data;
    new->next = NULL;
    new->prev = NULL;
    
    if (!(cache->size < cache->capacity))
    {
        removeLast(cache);
        (cache->size)--;
    }
    
    if (cache->head)
    {
        new->next = cache->head;
        cache->head->prev = new;
    }
    else
    {
        new->next = cache->head;
    }
    cache->head = new;
    /*look*/
    if (!cache->tail)
    {
        cache->tail = new;
    }
    
    (cache->size)++;
}

void moveToFront(Cache *cache, Node *node) { 
    if (cache->head == node)
    {
        return;
    }
    else
    {
        if (cache->tail == node)
        {
            cache->tail = node->prev;
            node->prev->next = NULL;
            node->prev = NULL;
        }
        else
        {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            node->prev = NULL;
        }
    }
    node->next = cache->head;
    cache->head->prev = node;
    cache->head = node;
    if (!cache->tail)
    {
        cache->tail = node;
    }
    /*not inclusive*/
}

void removeLast(Cache *cache) { 
    
    Node *trav = cache->tail;
    if(trav)
    {
        if(trav->prev)
        {
            trav->prev->next = NULL;
            cache->tail = trav->prev;
        }
        else
        {
            cache->head = NULL;
        }
        free(trav);
        (cache->size)--;
    }
}

User *fetchUser(int userId) { 
    Node *trav = userCache.head;
    
    while(trav)
    {
        User *user = trav->data;
        if(user->userId == userId)
        {
            moveToFront(&userCache, trav);
            return user;
        }
        trav = trav->next;
    }
    
    appendToCache(&userCache, &db.users[userId]);
    return &db.users[userId];
}

Post *fetchPost(int postId) { 
    Node *trav = postCache.head;
    
    while(trav)
    {
        Post *post = trav->data;
        if(post->postId == postId)
        {
            moveToFront(&postCache, trav);
            return post;
        }
        trav = trav->next;
    }
    
    appendToCache(&postCache, &db.posts[postId]);
    return &db.posts[postId];
}

void followUser(int followerId, int followedId) {
    /* TODO Fetch followerId, followedId, then update followers of followedId */
    User *follower = fetchUser(followerId);
    User *followed = fetchUser(followedId);
    Node *follower_node = createNode(follower);
    
    if (followed->followers_tail)
    {
        followed->followers_tail->next = follower_node;
        follower_node->prev = followed->followers_tail;
        followed->followers_tail = follower_node;
    }
    else
    {
        followed->followers_head = follower_node;
        followed->followers_tail = follower_node;
    }
    followed->numOfFollowers++;
    follower->numOfFollowing++;
    
    
}

void likePost(int userId, int postId) { 
    /* TODO Fetch userId and postId */ 
    fetchUser(userId)->liked++;
    fetchPost(postId)->likes++;
    
}

void printFollowersInReverse() {
    Node *trav = userCache.tail;
    printf("Followers of all users in UserCache in reverse:\n");
    /* For each user in the UserCache... */
    while (trav)
    {
        User *followed = trav->data;
        Node *follower_node = followed->followers_tail;
        printf("Followers of user with id %d in reverse:\n", followed->userId);
        while(follower_node)
        {
            User *follower = follower_node->data;
            printf("User %d follows user %d\n", follower->userId, followed->userId);
            follower_node = follower_node->prev;
        }
        trav = trav->prev;
    }
  
}

void freeLinkedList(Node *head) {
  /* TODO Free linked list nodes but not data or data's contents! */
    Node *trav = head;
    while (trav)
    {
        Node *tmp = trav;
        trav = trav->next;
        free(tmp);
    }
}

/* DO NOT CHANGE */
/* Only for implementation ease, not going to be used in evaluation */

int main(void) {
  int userCount;
  int postCount;
  int actionCount;
  int i;
  /* Read cache capacities */
  scanf("%d %d", &userCache.capacity, &postCache.capacity);

  /* Read users */
  scanf("%d", &userCount);
  for (i = 0; i < userCount; i++) {
    int userId;
    char username[USERNAME_MAX_LEN];
    int day, month, year;
    scanf("%d %s %d %d %d", &userId, username, &day, &month, &year);

    db.users[userId].userId = userId;
    db.users[userId].username = malloc(strlen(username));
    memcpy(db.users[userId].username, username, strlen(username) + 1);
    db.users[userId].birthday = malloc(sizeof(Date));
    db.users[userId].birthday->day = day;
    db.users[userId].birthday->month = month;
    db.users[userId].birthday->year = year;
    db.users[userId].followers_head = db.users[userId].followers_tail = NULL;
    db.users[userId].numOfFollowers = 0;
    db.users[userId].numOfFollowing = 0;
    db.users[userId].liked = 0;
  }

  /* Read posts */
  scanf("%d", &postCount);
  for (i = 0; i < postCount; i++) {
    int postId, authorId, content_length, j;
    char content[POST_CONTENT_MAX_LEN];
    scanf("%d %d %d ", &postId, &authorId, &content_length);
    for (j = 0; j < content_length; j++) {
      content[j] = getc(stdin);
    }
    content[content_length] = 0;

    db.posts[postId].postId = postId;
    db.posts[postId].author = &db.users[authorId];
    db.posts[postId].content = malloc(strlen(content));
    memcpy(db.posts[postId].content, content, strlen(content) + 1);
    db.posts[postId].likes = 0;
  }

  /* Do the actions */
  scanf("%d", &actionCount);
  for (i = 0; i < actionCount; i++) {
    char actionType[2];
    int id1, id2;
    if (i != 0) printf("\n\n");
    printf("Processing action %d\n", i + 1);
    scanf("%01s %d %d", actionType, &id1, &id2);
    if (actionType[0] == 'F') {
      /* Follow */
      followUser(id1, id2);
      printUserCache(&userCache);
    } else if (actionType[0] == 'L') {
      /* Like */
      likePost(id1, id2);
      printUserCache(&userCache);
      printf("\n");
      printPostCache(&postCache);
    } else {
      fprintf(stderr, "Unexpected action type '%s'!\n", actionType);
      exit(-1);
    }
  }
  /* At the end, print followers of all users in the UserCache */
  printf("\n\n");
  printFollowersInReverse();
  /* Free all */
  freeLinkedList(userCache.head);
  freeLinkedList(postCache.head);
  for (i = 0; i < DB_USER_CAPACITY; i++) {
    if (db.users[i].birthday) {
      free(db.users[i].birthday);
      free(db.users[i].username);
      freeLinkedList(db.users[i].followers_head);
    }
  }
  for (i = 0; i < DB_POST_CAPACITY; i++) {
    if (db.posts[i].content) {
      free(db.posts[i].content);
    }
  }
  return 0;
}

