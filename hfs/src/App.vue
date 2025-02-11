<script setup>
import QuizKnowledge from './components/quiz/QuizKnowledge.vue'
import OrigemIntro from './components/OrigemIntro.vue'
import SetePovosdasMissoes from './components/SetePovosdasMissoes.vue'
import OrganizacaoUrbanistica from './components/OrganizacaoUrbanistica.vue'
import OrganizacaoEconomica from './components/OrganizacaoEconomica.vue'
import GuerraGuaranitica from './components/GuerraGuaranitica.vue'
import QuizIntro from './components/QuizIntro.vue'
</script>

<template>
  <header class="jumbotron mission-header">
    <h1 class="text-light text-xl-center">JESUÍTAS E OS SETE POVOS DAS MISSÕES</h1>
  </header>

  <main class="container">
    <div class="text-left">
      <OrigemIntro />
      <SetePovosdasMissoes />
      <OrganizacaoUrbanistica />
      <OrganizacaoEconomica />
      <GuerraGuaranitica />
      <QuizIntro />
    </div>
    <QuizKnowledge />
  </main>
</template>

<style scoped>
.jumbotron.mission-header {
  padding: 0;
  background: url('assets/img/primeira-missa.jpg') center center no-repeat;
  background-size: cover;
  position: relative;
  height: 70vh;
  width: 100%;
}

.jumbotron.mission-header::before {
  content: '';
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
