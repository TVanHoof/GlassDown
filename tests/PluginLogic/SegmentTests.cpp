#include <gtest/gtest.h>

#include "Segment.h"

#include <cmath>

namespace {

// Segments are linear, so y is computed as (x - x_min) * slope + offset.
// Compare with a tolerance rather than exactly: slope involves a division.
constexpr double kTolerance = 1e-9;

} // namespace

TEST(SegmentTests, ContainsIncludesBothBoundaries) {
  const Segment seg(-1.0, -1.0, 1.0, 1.0);

  EXPECT_TRUE(seg.contains(-1.0));
  EXPECT_TRUE(seg.contains(0.0));
  EXPECT_TRUE(seg.contains(1.0));
}

TEST(SegmentTests, ContainsExcludesValuesOutsideRange) {
  const Segment seg(-1.0, -1.0, 1.0, 1.0);

  EXPECT_FALSE(seg.contains(-1.0000001));
  EXPECT_FALSE(seg.contains(1.0000001));
  EXPECT_FALSE(seg.contains(-42.0));
  EXPECT_FALSE(seg.contains(42.0));
}

TEST(SegmentTests, IdentitySegmentMapsInputToOutput) {
  // (-1,-1) -> (1,1): dx = 2, slope = 1, offset = -1, so y = (x + 1) * 1 - 1 = x
  const Segment seg(-1.0, -1.0, 1.0, 1.0);

  for(const double x : { -1.0, -0.5, 0.0, 0.5, 1.0 })
    EXPECT_NEAR(seg.applyLookup(x), x, kTolerance) << "at x = " << x;
}

TEST(SegmentTests, GainSegmentDoublesInput) {
  // (0,0) -> (0.5,1): dx = 0.5, slope = 1 / 0.5 = 2, offset = 0, so y = 2x
  const Segment seg(0.0, 0.0, 0.5, 1.0);

  for(const double x : { 0.0, 0.125, 0.25, 0.5 })
    EXPECT_NEAR(seg.applyLookup(x), 2.0 * x, kTolerance) << "at x = " << x;
}

TEST(SegmentTests, NegativeSlopeSegmentInvertsInput) {
  // (-1,1) -> (1,-1): slope = -2 / 2 = -1, offset = 1, so y = -(x + 1) + 1 = -x
  const Segment seg(-1.0, 1.0, 1.0, -1.0);

  for(const double x : { -1.0, -0.25, 0.0, 0.25, 1.0 })
    EXPECT_NEAR(seg.applyLookup(x), -x, kTolerance) << "at x = " << x;
}

TEST(SegmentTests, LookupExtrapolatesOutsideSegmentRange) {
  const Segment seg(0.0, 0.0, 0.5, 1.0);

  // applyLookup does not clamp; it extends the line. Graph is responsible for
  // deciding what to do with out-of-range input.
  EXPECT_NEAR(seg.applyLookup(-1.0), -2.0, kTolerance);
  EXPECT_NEAR(seg.applyLookup(1.0),  2.0, kTolerance);
}

TEST(SegmentTests, ZeroWidthSegmentReturnsOffsetWithoutDividing) {
  // dx == 0: slope stays 0 and applyLookup must return offset (= y1) rather
  // than dividing by zero.
  const Segment seg(1.0, 5.0, 1.0, 9.0);

  EXPECT_NEAR(seg.applyLookup(1.0), 5.0, kTolerance);
  EXPECT_TRUE(seg.contains(1.0));
}

TEST(SegmentTests, DefaultConstructedSegmentIsFlatAtZero) {
  const Segment seg;

  EXPECT_NEAR(seg.applyLookup(0.0), 0.0, kTolerance);
  EXPECT_NEAR(seg.getXMin(), 0.0, kTolerance);
  EXPECT_NEAR(seg.getXMax(), 0.0, kTolerance);
}

TEST(SegmentTests, UpdateRecomputesSlopeAndOffset) {
  Segment seg(-1.0, -1.0, 1.0, 1.0);
  EXPECT_NEAR(seg.applyLookup(0.5), 0.5, kTolerance);

  // Re-point the segment at (0,0) -> (0.5,1), i.e. a gain of 2.
  seg.update(0.0, 0.0, 0.5, 1.0);

  EXPECT_NEAR(seg.applyLookup(0.25), 0.5, kTolerance);
  EXPECT_NEAR(seg.getXMin(), 0.0, kTolerance);
  EXPECT_NEAR(seg.getXMax(), 0.5, kTolerance);
}

TEST(SegmentTests, GetXMinAndGetXMaxReportTheSegmentDomain) {
  const Segment seg(-2.0, 0.0, 4.0, 1.0);

  EXPECT_NEAR(seg.getXMin(), -2.0, kTolerance);
  EXPECT_NEAR(seg.getXMax(),  4.0, kTolerance);
}