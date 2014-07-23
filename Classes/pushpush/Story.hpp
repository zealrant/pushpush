#ifndef __PUSHPUSH_STORY_TELLER_HPP__
#define __PUSHPUSH_STORY_TELLER_HPP__

enum STORY_TYPE {
    STAGE_INTRO,
    STAGE_OUTRO
};

class Story {
  public:
    virtual void tell()=0;
    virtual void tell(std::function<void()> callback)=0;
    virtual void tellInner()=0;
};

class StoryFactory {
  public:
    virtual Story* get(STORY_TYPE type, int storyId)=0;
    virtual Story* get(STORY_TYPE type)=0;
};

#endif
