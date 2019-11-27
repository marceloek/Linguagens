<template>
  <div id="app">
    <div class="jumbotron mission-header">
      <h1 class="text-light text-xl-center">JESUÍTAS E OS SETE POVOS DAS MISSÕES</h1>
    </div>
    <div class="container">
      <div class="text-left">

        <Origem />
        <SetePovosdasMissoes />
        <OrganizacaoUrbanistica />
        <OrganizacaoEconomica />
        <GuerraGuaranitica />
        <QuizIntro />

      </div>
      <Quiz />
    </div>
  </div>
</template>

<script>
import Quiz from "./components/quiz/Quiz.vue";
import Origem from "./components/Origem";
import SetePovosdasMissoes from "./components/SetePovosdasMissoes";
import OrganizacaoUrbanistica from "./components/OrganizacaoUrbanistica";
import OrganizacaoEconomica from "./components/OrganizacaoEconomica";
import GuerraGuaranitica from "./components/GuerraGuaranitica";
import QuizIntro from "./components/QuizIntro";

export default {
  name: "app",
  components: {
    Quiz,
    Origem,
    SetePovosdasMissoes,
    OrganizacaoUrbanistica,
    OrganizacaoEconomica,
    GuerraGuaranitica,
    QuizIntro
  }
};
</script>

<style>

#app {
  font-family: "Avenir", Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}

.jumbotron.mission-header {
  padding: 0;
  background: url('assets/primeiramissasp.jpg') center center no-repeat;
  background-size: cover;
  position: relative;
  height: 70vh;
  width: 100%;
}

.jumbotron.mission-header::before {
  content: "";
  position: absolute;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background: rgba(0.4, 0.4, 0.4, 0.4);
  z-index: 0;
}

.jumbotron.mission-header h1 {
  position: absolute;
  z-index: 1;
  width: 100%;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
}

.mission-section {
  margin: 4rem 0;
}
</style>
