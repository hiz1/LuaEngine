//#include "Message.h"
//
//ofEvent<void> pageEjectionEvent;
//vector<ofPtr<Message> > textMessages;
//
//int l_newMessage(lua_State* L) {
//  textMessages.push_back(ofPtr<Message>(
//    new Message(ofRectangle(
//      luaL_checknumber(L, 1),
//      luaL_checknumber(L, 2),
//      luaL_checknumber(L, 3),
//      luaL_checknumber(L, 4)
//  ))));
//  textMessages[textMessages.size()-1]->text = ofPtr<string>(new string(""));
//  Message **a = (Message **)lua_newuserdata(L, sizeof(Message *));
//  *a = textMessages[textMessages.size()-1].get();
//  luaL_getmetatable(L, "app.message");
//  lua_setmetatable(L, -2);
//  return 1;
//}
//
//int l_deleteMessage(lua_State *L) {
//  Message *msg = *(Message **)lua_touserdata(L, 1);
//  for(vector<ofPtr<Message> >::iterator ite = textMessages.begin(); ite != textMessages.end(); ite ++) {
//    if((*ite).get() == msg) {
//      textMessages.erase(ite);
//      return 0;
//    }
//  }
//  return 0;
//}
//
//int l_say(lua_State *L) {
//  Message *message = *(Message **)lua_touserdata(L, 1);
//  string text    = luaL_checkstring(L, 2);
//  lua_getglobal(L, "Message");
//  message->text.reset(new string(text));
//  message->messageFinished = false;
//  message->textCursor      = 0;
//  return 0;
//}
//
//int l_updateMessage(lua_State *L) {
//  Message *message = *(Message **)lua_touserdata(L, 1);
//  message->update();
//  return 0;
//}
//
//int l_dequeMessage(lua_State *L) {
//  lua_getglobal(L, "Message");
//  Message *msg = (Message *)lua_touserdata(L, -1);
//  lua_pushboolean(L, msg->deque());
//  return 1;
//}
//
//static const struct luaL_Reg engineLib_message_m [] = {
//  {"delete"         , l_deleteMessage},
//  {"say"            , l_say},
//  {"update"         , l_updateMessage},
//  {"draw"           , l_drawMessage},
//  {"deque"          , l_dequeMessage},
//  {NULL, NULL}
//};
//
//static const struct luaL_Reg engineLib_message_f [] = {
//  {"new"            , l_newMessage},
//  {NULL, NULL}
//};
//
//void openlib_Message(lua_State *L) {
//  lua_settop(L, 0);
//  luaL_newmetatable(L, "app.image");
//  // set GC
//  lua_pushstring(L, "__gc");
//  lua_pushcfunction(L, l_deleteMessage);
//  lua_settable(L, -3);
//  // set method
//  lua_pushvalue(L, -1);
//  lua_setfield(L, -2, "__index");
//  luaL_register(L, NULL, engineLib_message_m);
//  // set constructer
//  luaL_register(L, "image", engineLib_message_f);
//}
//
////--------------------------------------------------------------
//Message::Message(ofRectangle rect){
//  textCursor=0;
//  this->rect = rect;
//  ofAddListener(dequeMessageEvent, this, &Message::deque);
//}
//
//bool Message::deque() {
//  if(textCursor < utf8len(*text)) return false;
//  messageFinished = true;
//  return true;
//}
//
////--------------------------------------------------------------
//bool Message::update(){
//  if(messageFinished) return false;
//  textCursor += 0.5;
//}
//
//void Message::draw() {
//  
//}
//
//
////void drawMessageWindow(ofxTrueTypeFontUC &font, const string &text, bool completed, int height, int radius = 20, int margin=10,int padding=20) {
////  // draw a message window
////  ofRectangle rect = ofRectangle(margin,ofGetHeight() - height + margin,ofGetWidth() - margin * 2,height - margin * 2);
////  ofEnableAlphaBlending();
////  // draw inside
////  ofSetColor(255,255,255,122);
////  ofFill();
////  ofRectRounded(rect, radius);
////  // draw frame
////  ofNoFill();
////  ofSetColor(0,0,0,61);
////  ofSetLineWidth(4);
////  ofRectRounded(rect, radius);
////  ofSetColor(0,0,0,122);
////  ofSetLineWidth(2);
////  ofRectRounded(rect, radius);
////  // draw text
////  if(text.size() > 0) {
////    ofSetColor(0,0,0,255);
////    font.drawString(text, margin + padding, ofGetHeight() - height + margin + padding, TOP_LEFT);
////    if(completed) {
////      ofFill();
////      ofSetColor(0,0,0,255);
////      int baseX = ofGetWidth()/2, baseY = ofGetHeight() - margin + sin(ofGetElapsedTimef()*PI*3.5)*1.5;
////      ofTriangle(baseX, baseY + 2, baseX - 8, baseY - 10, baseX + 8, baseY - 10);
////    }
////  }
////}
//
