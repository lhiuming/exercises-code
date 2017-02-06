// sourve file for Picture.h
#include "Picture.h"
#include <string>
#include <vector>
#include "Ptr.h"
#include "Ptr.cpp" // avoid linker comlain
#include <algorithm>

using std::string;
using std::vector;
using std::ostream;
using std::endl;
using std::max;

// Picture creations
Picture frame(const Picture& pic) {
  // notice： Picture has a convertor from Pic_base
  // so the following calls 2 constructor.
  return new Frame_Pic(pic.p);
}

Picture hcat(const Picture& l, const Picture& r)
{
  return new HCat_Pic(l.p, r.p);
}

Picture vcat(const Picture& t, const Picture& b)
{
  return new VCat_Pic(t.p, b.p);
}

// output operator
ostream& operator<<(ostream& os, const Picture& picture)
{
  const Pic_base::ht_sz ht = picture.p->height();
  for (Pic_base::ht_sz i = 0; i != ht; ++i) {
    picture.p->display(os, i, false);
    os << endl;
  }
  return os;
}


// Pic_base and derevitives
Pic_base::wd_sz String_Pic::width() const {
  Pic_base::wd_sz n = 0;
  for (Pic_base::ht_sz i = 0; i != data.size(); ++i)
    n = max(n, data[i].size());
  return n;
}

void String_Pic::display(ostream& os, ht_sz row, bool do_pad) const
{
  wd_sz start = 0; // default 0: will pad a blank line if rwo>=height

  // check range and write
  if (row < height()) {
    os << data[row];
    start = data[row].size();
  }

  // pad if required
  if (do_pad)
    pad(os, start, width());
}

void VCat_Pic::display(ostream& os, ht_sz row, bool do_pad) const
{
  wd_sz w = 0; // default 0: for blank line padding

  if (row < top->height()) {
    // now is in the top part
    top->display(os, row, do_pad);
    w = top->width();
  } else if (row < height()) {
    // now is in the bottom part
    bottom->display(os, row - top->height(), do_pad);
    w = bottom->width();
  }

  if (do_pad)
    pad(os, w, width());
}

void HCat_Pic::display(ostream& os, ht_sz row, bool do_pad) const
{
  left->display(os, row, do_pad || row < right->height());
  right->display(os, row, do_pad);
}

void Frame_Pic::display(ostream& os, ht_sz row, bool do_pad) const
{
  if (row >= height()) {
    // when out of range
    if (do_pad)
      pad(os, 0, width());
  } else {
    if (row == 0 || row == height() - 1) {
      os << string(width(), '*');
    } else if (row == 1 || row == height() - 2) {
      os << "*";
      pad(os, 1, width() - 1);
      os << "*";
    } else {
      // interior row that has content
      os << "* ";
      p->display(os, row - 2, true);
      os << " *";
    }
  }
}

// Picture constructor
Picture::Picture(const vector<string>& v):
  // using Ptr(T*) constructor
  p(new String_Pic(v)) {}
