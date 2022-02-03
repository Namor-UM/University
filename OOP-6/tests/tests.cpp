#include "gtest/gtest.h"
#include "Base64.h"


TEST(Encode, case){
    EXPECT_EQ(encode("Well, let’s just say hypotetically ok? What if they have a good personality?"), "V2VsbCwgbGV04oCZcyBqdXN0IHNheSBoeXBvdGV0aWNhbGx5IG9rPyBXaGF0IGlmIHRoZXkgaGF2ZSBhIGdvb2QgcGVyc29uYWxpdHk/");
    EXPECT_EQ(encode("I have to return some videotapes."), "SSBoYXZlIHRvIHJldHVybiBzb21lIHZpZGVvdGFwZXMu");
    EXPECT_EQ(encode("You are fucking ugly bitch! I want to stab you to death and play around with your blood."), "WW91IGFyZSBmdWNraW5nIHVnbHkgYml0Y2ghIEkgd2FudCB0byBzdGFiIHlvdSB0byBkZWF0aCBhbmQgcGxheSBhcm91bmQgd2l0aCB5b3VyIGJsb29kLg==");
    EXPECT_EQ(encode("Look at that subtle off-white coloring; the tasteful thickness of it… Oh my God, it even has a watermark."), "TG9vayBhdCB0aGF0IHN1YnRsZSBvZmYtd2hpdGUgY29sb3Jpbmc7IHRoZSB0YXN0ZWZ1bCB0aGlja25lc3Mgb2YgaXTigKYgT2ggbXkgR29kLCBpdCBldmVuIGhhcyBhIHdhdGVybWFyay4=");
    EXPECT_EQ(encode("I like to dissect girls. Did you know that I am utterly insane?"), "SSBsaWtlIHRvIGRpc3NlY3QgZ2lybHMuIERpZCB5b3Uga25vdyB0aGF0IEkgYW0gdXR0ZXJseSBpbnNhbmU/");
    EXPECT_EQ(encode(""), "");
}


TEST(Decode_correct, case){
    EXPECT_EQ(decode("Q29vbCBmZW1ib3kgZmFjdDogT05FIERBWSBZT1UgV0lMTCBIQVZFIFRPIEFOU1dFUiBGT1IgWU9VUiBBQ1RJT05TIEFORCBHT0QgTUFZIE5PVCBCRSBTTyBNRVJDSUZVTC4="), "Cool femboy fact: ONE DAY YOU WILL HAVE TO ANSWER FOR YOUR ACTIONS AND GOD MAY NOT BE SO MERCIFUL.");
    EXPECT_EQ(decode("RnJpZW5kcyBpcyBhIGdyaXR0eSBkb2N1bWVudGFyeS4gVGhlIHNldHRpbmcgb2YgdGhpcyBjaXR5IGluIEhvbmcgS29uZy4gU3RhcnJpbmc6IENoYW5kbGVyLCBTb3JvcywgUGhvYm9zIDEsIFJhY2hlbCwgTW9uaWNhLiBBbmQgc29tZSBvdGhlciBmdWNraW5nIGFjdG9ycy4="),
              "Friends is a gritty documentary. The setting of this city in Hong Kong. Starring: Chandler, Soros, Phobos 1, Rachel, Monica. And some other fucking actors.");
    EXPECT_EQ(decode("TWF5IGJlIHlvdSBhbmQgSSBjb3VsZCBwYXJ0bmVyIHVwPw=="), "May be you and I could partner up?");
    EXPECT_EQ(decode("U1RPUCBQT1NUSU5HIEFCT1VUIEFNT05HIFVTIQ=="), "STOP POSTING ABOUT AMONG US!");
    EXPECT_EQ(decode(""), "");
}


TEST(Decode_incorrect, case){
    EXPECT_ANY_THROW(decode("AMOUNTOFGENDERS=2"));
    EXPECT_ANY_THROW(decode("8==="));
    EXPECT_ANY_THROW(decode("mynamesjeff"));
    EXPECT_ANY_THROW(decode("|D|2!\\/37 |<057!4"));
}