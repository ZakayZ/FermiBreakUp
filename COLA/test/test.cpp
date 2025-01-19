#include <COLA.hh>
#include <gtest/gtest.h>
#include <CLHEP/Units/PhysicalConstants.h>

#include "G4HandlerModule.h"

namespace {

  class TestGenerator: public cola::VGenerator {
  public:
    TestGenerator(const cola::EventParticles& particles) : particles_(particles) {}

    std::unique_ptr<cola::EventData> operator()() override {
      auto data = std::make_unique<cola::EventData>();
      data->particles = particles_;

      return data;
    }

  private:
    const cola::EventParticles particles_;
  };

  class TestGeneratorFactory: public cola::VFactory {
  public:
    cola::VFilter* create(const std::map<std::string, std::string>&) override {
      return new TestGenerator(particles);
    }

    cola::EventParticles particles;
  };

  class TestWriter: public cola::VWriter {
  public:
    TestWriter(std::vector<std::unique_ptr<cola::EventData>>& holder) : events_(holder) {}

    void operator()(std::unique_ptr<cola::EventData>&& event) {
      events_.emplace_back(std::move(event));
    }

  private:
    std::vector<std::unique_ptr<cola::EventData>>& events_;
  };

  class TestWriterFactory: public cola::VFactory {
  public:
    cola::VFilter* create(const std::map<std::string, std::string>&) override {
      return new TestWriter(events);
    }

    std::vector<std::unique_ptr<cola::EventData>> events;
  };

  struct Wrapper {
    Wrapper(cola::VFactory* converter) {
      metaProcessor.reg(std::unique_ptr<cola::VFactory>(genFactory), "generator", cola::FilterType::generator);
      metaProcessor.reg(std::unique_ptr<cola::VFactory>(converter), "converter", cola::FilterType::converter);
      metaProcessor.reg(std::unique_ptr<cola::VFactory>(writerFactory), "writer", cola::FilterType::writer);
    }

    void Run(int n = 1) {
      auto manager = cola::ColaRunManager(metaProcessor.parse("config.xml"));
      manager.run(n);
    }

    cola::MetaProcessor metaProcessor;
    TestGeneratorFactory* genFactory = new TestGeneratorFactory();
    TestWriterFactory* writerFactory = new TestWriterFactory();
  };

  bool operator==(const cola::Particle& a, const cola::Particle& b) {
    return a.position == b.position
          && a.momentum == b.momentum
          && a.pdgCode == b.pdgCode
          && a.pClass == b.pClass;
  }

} // anonymous namespace

TEST(TestModule, TestFermi) {
  auto wrapper = Wrapper(new cola::FermiFactory());

  {
    auto particle = cola::Particle{
      .position=cola::LorentzVector{},
      .momentum=cola::LorentzVector{
        .e=std::sqrt(3 * std::pow(100 * CLHEP::MeV, 2) + std::pow(4 * 936 * CLHEP::MeV, 2)),
        .x=100 * CLHEP::MeV,
        .y=100 * CLHEP::MeV,
        .z=100 * CLHEP::MeV,
      },
      .pdgCode=cola::AZToPdg({4, 2}),
      .pClass=cola::ParticleClass::produced,
    };
    wrapper.genFactory->particles = {particle,};
    auto& events = wrapper.writerFactory->events;
    events.clear();

    ASSERT_NO_THROW(wrapper.Run());

    ASSERT_EQ(events.size(), 1);
    ASSERT_EQ(events[0]->particles.size(), 1);
    EXPECT_TRUE(particle == events[0]->particles[0]);
  }

  {
    auto particle = cola::Particle{
      .position=cola::LorentzVector{},
      .momentum=cola::LorentzVector{
        .e=std::sqrt(3 * std::pow(100 * CLHEP::MeV, 2) + std::pow(5 * 938 * CLHEP::MeV, 2)),
        .x=100 * CLHEP::MeV,
        .y=100 * CLHEP::MeV,
        .z=100 * CLHEP::MeV,
      },
      .pdgCode=cola::AZToPdg({5, 3}),
      .pClass=cola::ParticleClass::produced,
    };
    wrapper.genFactory->particles = {particle,};
    auto& events = wrapper.writerFactory->events;
    events.clear();

    ASSERT_NO_THROW(wrapper.Run());

    ASSERT_EQ(events.size(), 1);
    EXPECT_EQ(events[0]->particles.size(), 2);
  }
}

TEST(TestModule, TestG4Handler) {
  auto wrapper = Wrapper(new cola::G4HandlerFactory());

  {
    auto particle = cola::Particle{
      .position=cola::LorentzVector{},
      .momentum=cola::LorentzVector{
        .e=std::sqrt(3 * std::pow(100 * CLHEP::MeV, 2) + std::pow(4 * 938 * CLHEP::MeV, 2)),
        .x=100 * CLHEP::MeV,
        .y=100 * CLHEP::MeV,
        .z=100 * CLHEP::MeV,
      },
      .pdgCode=cola::AZToPdg({4, 2}),
      .pClass=cola::ParticleClass::produced,
    };
    wrapper.genFactory->particles = {particle,};
    auto& events = wrapper.writerFactory->events;
    events.clear();

    ASSERT_NO_THROW(wrapper.Run());

    ASSERT_EQ(events.size(), 1);
    ASSERT_EQ(events[0]->particles.size(), 2);
  }

  {
    auto particle = cola::Particle{
      .position=cola::LorentzVector{},
      .momentum=cola::LorentzVector{
        .e=std::sqrt(3 * std::pow(100 * CLHEP::MeV, 2) + std::pow(5 * 938 * CLHEP::MeV, 2)),
        .x=100 * CLHEP::MeV,
        .y=100 * CLHEP::MeV,
        .z=100 * CLHEP::MeV,
      },
      .pdgCode=cola::AZToPdg({5, 3}),
      .pClass=cola::ParticleClass::produced,
    };
    wrapper.genFactory->particles = {particle,};
    auto& events = wrapper.writerFactory->events;
    events.clear();

    ASSERT_NO_THROW(wrapper.Run());

    ASSERT_EQ(events.size(), 1);
    EXPECT_EQ(events[0]->particles.size(), 3);
  }
}
