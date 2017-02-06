#include <string>
#include <algorithm>

vector<string> find_urls(const string& s)
{
  vector<string> ret;
  typedef string::const_iterator iter;
  iter b = s.begin(), e = s.end();

  // look through the entire input
  while (b != e) {

    // look for one ore more letters followed by ://
    b = url_beg(b, e);

    // if there is any
    if (b != e) {
      // get the rest of the URL
      iter after = url_end(b, e);

      // store the URL
      ret.push_back(string(b, after));

      // advance b and check for more URLs on this line
      b = after;
    }
  }
  return ret;
}

string::const_iterator
url_end(string::const_iterator b, string::const_iterator e)
{
  return find_if(b, e, not_url_char);
}

bool not_url_char(char c)
{
  // charactors and others that can appear in a URL
  static const string url_ch = "~;?:@=&$-_.+!*'(),";

  // see whether c can appear in a URL and return the nagation
  return !(isalnum(c) ||
           find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}

string::const_iterator
url_beg(string::const_iterator b, string::const_iterator e)
{
  static const string sep = "://";

  typedef string::const_iterator iter;

  // i marks where the separator was found
  iter i = b;

  while ( (i = search(i, e, sep.begin(), sep.end())) != e) {
    // make sure that isn't at the beginning or end of the line
    if (i != b && i + sep.size() != e) {
      // beg marks the beginning of the protocol-name
      iter beg = i;
      while (beg != b && isalpha(beg[-1]))
        --beg;

      // is there at least one appropriate chracter before and after the sep
    if (beg != i && !not_url_char(i[sep.size()]))
      return beg;
    }

    // the seperator we found wasn't part of a URL, so advance i
    // note: we can't advance sep.size()+1 because we might fall out of the
    //       text
    i += sep.size();
  }
  return e;
}
