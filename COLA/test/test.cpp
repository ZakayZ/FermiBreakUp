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
      meta_processor.reg(std::unique_ptr<cola::VFactory>(gen_factory), "generator", cola::FilterType::generator);
      meta_processor.reg(std::unique_ptr<cola::VFactory>(converter), "converter", cola::FilterType::converter);
      meta_processor.reg(std::unique_ptr<cola::VFactory>(writer_factory), "writer", cola::FilterType::writer);
    }

    void Run(int n = 1) {
      auto manager = cola::ColaRunManager(meta_processor.parse("config.xml"));
      manager.run(n);
    }

    cola::MetaProcessor meta_processor;
    TestGeneratorFactory* gen_factory = new TestGeneratorFactory();
    TestWriterFactory* writer_factory = new TestWriterFactory();
  };

  bool operator==(const cola::Particle& a, const cola::Particle& b) {
    return a.x == b.x
          && a.y == b.y
          && a.z == b.z
          && a.pX == b.pX
          && a.pY == b.pY
          && a.pZ == b.pZ
          && a.pdgCode == b.pdgCode
          && a.pClass == b.pClass;
  }

} // anonymous namespace

TEST(TestModule, TestFermi) {
  auto wrapper = Wrapper(new cola::FermiFactory());

  {
    auto particle = cola::Particle{
      .x=0,
      .y=0,
      .z=0,
      .pX=100 * CLHEP::MeV,
      .pY=100 * CLHEP::MeV,
      .pZ=100 * CLHEP::MeV,
      .pdgCode=cola::AZToPdg({4, 2}),
      .pClass=cola::ParticleClass::produced,
    };
    wrapper.gen_factory->particles = {particle,};
    auto& events = wrapper.writer_factory->events;
    events.clear();

    ASSERT_NO_THROW(wrapper.Run());

    ASSERT_EQ(events.size(), 1);
    ASSERT_EQ(events[0]->particles.size(), 1);
    EXPECT_TRUE(particle == events[0]->particles[0]);
  }

  {
    auto particle = cola::Particle{
      .x=0,
      .y=0,
      .z=0,
      .pX=100 * CLHEP::MeV,
      .pY=100 * CLHEP::MeV,
      .pZ=100 * CLHEP::MeV,
      .pdgCode=cola::AZToPdg({5, 3}),
      .pClass=cola::ParticleClass::produced,
    };
    wrapper.gen_factory->particles = {particle,};
    auto& events = wrapper.writer_factory->events;
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
      .x=0,
      .y=0,
      .z=0,
      .pX=100 * CLHEP::MeV,
      .pY=100 * CLHEP::MeV,
      .pZ=100 * CLHEP::MeV,
      .pdgCode=cola::AZToPdg({4, 2}),
      .pClass=cola::ParticleClass::produced,
    };
    wrapper.gen_factory->particles = {particle,};
    auto& events = wrapper.writer_factory->events;
    events.clear();

    ASSERT_NO_THROW(wrapper.Run());

    ASSERT_EQ(events.size(), 1);
    ASSERT_EQ(events[0]->particles.size(), 1);
  }

  {
    auto particle = cola::Particle{
      .x=0,
      .y=0,
      .z=0,
      .pX=100 * CLHEP::MeV,
      .pY=100 * CLHEP::MeV,
      .pZ=100 * CLHEP::MeV,
      .pdgCode=cola::AZToPdg({5, 3}),
      .pClass=cola::ParticleClass::produced,
    };
    wrapper.gen_factory->particles = {particle,};
    auto& events = wrapper.writer_factory->events;
    events.clear();

    ASSERT_NO_THROW(wrapper.Run());

    ASSERT_EQ(events.size(), 1);
    EXPECT_EQ(events[0]->particles.size(), 3);
  }
}


// int main() {
//   cola::MetaProcessor meta_processor;
//   auto writer_factory = new TestWriterFactory();
//   auto generator_factory = new TestGeneratorFactory();
//   meta_processor.reg(std::unique_ptr<cola::VFactory>(generator_factory), "generator", cola::FilterType::generator);
//   meta_processor.reg(std::unique_ptr<cola::VFactory>(new ExCFactory), "converter", cola::FilterType::converter);
//   meta_processor.reg(std::unique_ptr<cola::VFactory>(writer_factory), "writer", cola::FilterType::writer);

//   // Assemble manager and run
//   cola::ColaRunManager manager(meta_processor.parse("config.xml"));
//   manager.run();
// }
